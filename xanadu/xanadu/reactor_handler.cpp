//

#include "player.hpp"
#include "reactor.hpp"
#include "map.hpp"
#include <iostream>

void Player::handle_hit_reactor()
{
	int reactorid = read<int>();
	int pos = read<int>();
	short stance = read<short>();
	get_map()->hit_reactor(reactorid, this);
}
