//

#include "player.hpp"
#include <iostream>

void Player::handle_hit_reactor()
{
	int reactorid = read<int>();
	int pos = read<int>();
	short stance = read<short>();
	std::cout << "goodbye" << std::endl;
	/*Reactor *reactor = player->getMap()->getReactor(reactorid);

	if (!reactor)
	{
		return;
	}

	get_map()->getReactors()->hitReactor(reactor, player, stance, pos);*/
}
