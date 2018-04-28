//

#pragma once

#include <unordered_map>

class Map;
class Player;

class Reactor {
public:

	// constructor
	Reactor(Map *map, int reactor_id, int object_id, short position_x, short position_y, signed char stance, signed char state);

	// default constructor
	Reactor() = delete;

	// copy constructor
	Reactor(const Reactor &other) = delete;

	// move constructor
	Reactor(Reactor &&other) = delete;

	// destructor
	~Reactor() = default;

	// copy assignment operator
	Reactor &operator=(const Reactor &other) = delete;

	// move assignment operator
	Reactor &operator=(Reactor &&other) = delete;

	bool can_revive();
	bool is_dead();
	signed char get_stance();
	signed char get_state();
	short get_position_x();
	short get_position_y();
	int get_object_id();
	int get_reactor_id();
	Player *get_owner();
	void set_is_dead(bool dead);
	void set_owner(Player *owner);
	void reset();
	short set_state(Player *player);

private:

	bool is_dead_;
	signed char stance_;
	short position_x_;
	short position_y_;
	int object_id_;
	int reactor_id_;
	signed char state_;
	short life_;
	time_t time_dead_;
	time_t last_hit_;
	Map *map_;
	Player *current_owner_;
};
