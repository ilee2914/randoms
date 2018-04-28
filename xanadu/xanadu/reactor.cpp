#include "reactor.hpp"

#include "map.hpp"
#include "packetcreator.hpp"
#include <iostream>

Reactor::Reactor(Map *map, int reactor_id, int object_id, short position_x, short position_y, signed char stance, signed char state) :
	map_(map),
	reactor_id_(reactor_id),
	object_id_(object_id),
	position_x_(position_x),
	position_y_(position_y),
	stance_(stance),
	state_(state),
	life_(4),
	is_dead_(false),
	last_hit_(0),
	current_owner_(nullptr) {
}

bool Reactor::can_revive() {
	std::cout << time(nullptr) - time_dead_ << std::endl;
	return time(nullptr) - time_dead_ >= 10;
}
bool Reactor::is_dead() {
	return is_dead_;
}

signed char Reactor::get_stance() {
	return stance_;
}

signed char Reactor::get_state() {
	return state_;
}

short Reactor::get_position_x() {
	return position_x_;
}

short Reactor::get_position_y() {
	return position_y_;
}

int Reactor::get_object_id() {
	return object_id_;
}

int Reactor::get_reactor_id() {
	return reactor_id_;
}

Player *Reactor::get_owner() {
	return current_owner_;
}
void Reactor::set_is_dead(bool dead) {
	if (dead) {
		time_dead_ = time(nullptr);
	}
	is_dead_ = dead;
}
void Reactor::set_owner(Player *owner) {
	current_owner_ = owner;
}
void Reactor::reset() {
	set_owner(nullptr);
	life_ = 0;
	time_dead_ = 0;
	state_ = 0;
	last_hit_ = 0;
	is_dead_ = false;
	{
		PacketCreator packet;
		packet.SpawnReactor(this);
		map_->send_packet(&packet);
	}
}

short Reactor::set_state(Player *player) {
	set_owner(player);
	if (time(nullptr) - last_hit_ > 1) {
		state_++;
		last_hit_ = time(nullptr);
		return state_;
	} else {
		return -1;
	}	
}
