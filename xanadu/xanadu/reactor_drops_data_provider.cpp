//

#include "reactor_drops_data_provider.hpp"

#include "drop_data.hpp"
#include "world.hpp"

#include "Poco\Data\RecordSet.h"

// singleton

ReactorDropsDataProvider *ReactorDropsDataProvider::singleton_ = nullptr;

ReactorDropsDataProvider *ReactorDropsDataProvider::get_instance() {
	if (!singleton_) {
		singleton_ = new ReactorDropsDataProvider();
	}

	return singleton_;
}

void ReactorDropsDataProvider::load_data() {
	// get the dropper id's

	Poco::Data::Session session = World::get_instance()->get_mysql_session();

	Poco::Data::Statement statement1(session);
	statement1 << "SELECT reactorid FROM reactordrops GROUP BY reactorid";
	statement1.execute();

	Poco::Data::RecordSet recordset1(statement1);

	for (size_t col = 0; col < recordset1.rowCount(); ++col) {
		std::vector<DropData *> drops;

		int reactorid = recordset1["reactorid"];

		Poco::Data::Statement statement2(session);
		statement2 << "SELECT itemid, questid, chance FROM reactordrops WHERE reactorid = " << reactorid; // NOTE: exclude mesos at the moment
		statement2.execute();

		Poco::Data::RecordSet recordset2(statement2);

		for (size_t row_num = 0; row_num < recordset2.rowCount(); ++row_num) {
			// WORKAROUND
			// not using quest item drops at the moment so they dont drop all the time

			int quest_id = recordset2["questid"];
			int item_id = recordset2["itemid"];
			int chance = recordset2["chance"];

			DropData *drop_data = new DropData();
			drop_data->item_id = item_id;
			drop_data->chance = chance;
			drop_data->questitem = quest_id;

			drops.push_back(drop_data);

			recordset2.moveNext();
		}

		drops_[reactorid] = drops;

		recordset1.moveNext();
	}
}

std::vector<DropData *> *ReactorDropsDataProvider::get_drop_data(int rid) {
	if (drops_.find(rid) == drops_.end()) {
		return nullptr;
	}

	return &drops_[rid];
}
