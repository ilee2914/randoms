//

#pragma once

#include <unordered_map>

struct DropData;

class ReactorDropsDataProvider {
public:

	// default constructor
	ReactorDropsDataProvider() = default;

	// copy constructor
	ReactorDropsDataProvider(const ReactorDropsDataProvider &other) = delete;

	// move constructor
	ReactorDropsDataProvider(ReactorDropsDataProvider &&other) = delete;

	// destructor
	~ReactorDropsDataProvider() = default;

	// copy assignment operator
	ReactorDropsDataProvider &operator=(const ReactorDropsDataProvider &other) = delete;

	// move assignment operator
	ReactorDropsDataProvider &operator=(ReactorDropsDataProvider &&other) = delete;

	static ReactorDropsDataProvider *get_instance();
	void load_data();
	std::vector<DropData *> *get_drop_data(int mob_id);

private:

	static ReactorDropsDataProvider *singleton_;
	std::unordered_map<int, std::vector<DropData *>> drops_;
};
