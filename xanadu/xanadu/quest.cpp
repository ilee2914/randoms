//

#include "quest.hpp"

#include "quest_data_provider.hpp"
#include "quest_data.hpp"
#include <iostream>
// constructor

Quest::Quest(int id, bool completed, bool custom = false) :
	
	completed_(completed),
	id_(id),
	custom_(custom) {
}

bool Quest::add_killed_mob(int id, int amount) {
	QuestData *data = QuestDataProvider::get_instance()->get_quest_data(id_);
	if (!data) {
		return false;
	}

	auto required_monsters = *data->get_required_mobs();
	if (required_monsters.find(id) == required_monsters.end()) {
		return false;
	}

	int required_kills = required_monsters[id];

	if (killed_mobs_.find(id) != killed_mobs_.end()) {
		if (killed_mobs_[id] >= required_kills) {
			return false;
		}

		killed_mobs_[id] += amount;
	} else {
		killed_mobs_[id] = amount;
	}

	return true;
}

void Quest::set_completed() {
	completed_ = true;
}

bool Quest::is_completed() {
	return completed_;
}

bool Quest::is_custom() {
	return custom_;
}

int Quest::get_id() {
	if (this != nullptr)
		return id_;
	return 0;
}

long long Quest::get_completion_time() {
	return 0;
}

std::string Quest::get_killed_mobs1() {
	std::string ret;
	for (auto &it : killed_mobs_) {
		char temp[4];
		int amount = it.second;
		temp[0] = amount / 100 + '0';
		temp[1] = amount / 10 % 10 + '0';
		temp[2] = amount % 10 + '0';
		temp[3] = '\0';
		ret += std::string(temp);
	}
	return ret;
}

std::unordered_map<int, int> *Quest::get_killed_mobs2() {
	return &killed_mobs_;
}
