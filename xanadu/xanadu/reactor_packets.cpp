//

#include "map_reactor_data.hpp"
#include "packetcreator.hpp"
#include "send_packet_opcodes.hpp"
#include "reactor.hpp"

void PacketCreator::SpawnReactor(Reactor *reactor) {
	write<short>(send_headers::kREACTOR_SPAWN);
	write<int>(reactor->get_object_id());
	write<int>(reactor->get_reactor_id());
	write<signed char>(reactor->get_state());
	write<short>(reactor->get_position_x());
	write<short>(reactor->get_position_y());
	write<signed char>(reactor->get_stance());
	write<std::string>(""); // reactor name
}

void PacketCreator::DestroyReactor(Reactor *reactor) {
	write<short>(send_headers::kREACTOR_DESTROY);
	write<int>(reactor->get_object_id());
	write<signed char>(reactor->get_state());
	write<short>(reactor->get_position_x());
	write<short>(reactor->get_position_y());
}

void PacketCreator::triggerReactor(Reactor *reactor) {
	write<short>(send_headers::kREACTOR_HIT);
	write<int>(reactor->get_object_id());
	write<signed char>(reactor->get_state());
	write<short>(reactor->get_position_x());
	write<short>(reactor->get_position_y());
	write<signed char>(reactor->get_stance());
	write<int>(0);
	write<int>(5);

}