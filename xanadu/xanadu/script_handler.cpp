
#include "script_handler.h"

#include "player.hpp"
#include "map.hpp"
#include "playernpc.hpp"
#include "session.hpp"
#include "constants.hpp"

#include "duktape-2.2.0\src\duktape.h"
#include "dukglue-master\include\dukglue\dukglue.h"
#ifndef io
#define io
#include <iostream>

using namespace std;
#endif
// Implement a simple message callback function for as

// constants for as

const int as_YES_CONSTANT = kNpcConstantsYes;
const int as_NO_CONSTANT = kNpcConstantsNo;

const int as_EQUIP = kInventoryConstantsTypesEquip;
const int as_USE = kInventoryConstantsTypesUse;
const int as_SETUP = kInventoryConstantsTypesSetup;
const int as_ETC = kInventoryConstantsTypesEtc;
const int as_CASH = kInventoryConstantsTypesCash;

void Player::npc_script_handler(int mode, int type, int selection) {
	// Handles file loading
	if (!ctx || mode == 0) {
		duk_destroy_heap(ctx);
		int npc_id = npc_->id_;

		std::string npc_id_string = std::to_string(npc_id);
		std::string file_name_string = "scripts\\npcs\\" + npc_id_string + ".js";
		FILE *f = fopen(file_name_string.c_str(), "rb");

		if (!f) {
			file_name_string = "scripts\\npcs\\default.js";
			f = fopen(file_name_string.c_str(), "rb");
		}
		char buf[16384];
		size_t len = fread((void *)buf, 1, sizeof(buf), f);
		fclose(f);

		ctx = duk_create_heap_default();
		if (!ctx) return;
		duk_push_lstring(ctx, (const char *)buf, (duk_size_t)len);

		try {
			if (duk_peval(ctx) != 0) {
				cout << "goofed" << endl;
				return;
			}
		} catch (DukErrorException e) {
			cout << "ERROR : " << e.what() << endl;
		}
		
		duk_pop(ctx);

		dukglue_register_method(ctx, &Player::send_ok, "sendOk");
		dukglue_register_method(ctx, &Player::send_simple, "sendSimple");
		dukglue_register_method(ctx, &Player::send_next, "sendNext");
		dukglue_register_method(ctx, &Player::send_back_ok, "sendPrev");
		dukglue_register_method(ctx, &Player::send_yes_no, "sendYesNo");
		dukglue_register_method(ctx, &Player::send_back_next, "sendNextPrev");
		dukglue_register_method(ctx, &Player::send_accept_decline, "sendAcceptDecline");
		//dukglue_register_method(ctx, &Player::send_style, "sendStyle");
		dukglue_register_method(ctx, &Player::send_get_number, "sendGetNumber");
		dukglue_register_method(ctx, &Player::send_get_text, "sendGetText");

		dukglue_register_method(ctx, &Player::disposeChat, "dispose");
		
		dukglue_register_method(ctx, &Player::get_mesos, "getMeso");
		dukglue_register_method(ctx, &Player::get_job, "getJobId");
		dukglue_register_method(ctx, &Player::add_mesos, "gainMeso");
		dukglue_register_method(ctx, &Player::gain_exp, "gainExp");
		dukglue_register_method(ctx, &Player::get_level, "getLevel");
		dukglue_register_method(ctx, &Player::get_name, "getName");
		dukglue_register_method(ctx, &Player::get_gender, "getGender");
		
		dukglue_register_method(ctx, &Player::set_hair, "setHair");
		dukglue_register_method(ctx, &Player::set_face, "setFace");
		dukglue_register_method(ctx, &Player::set_skin_color, "setSkin");

		dukglue_register_method(ctx, &Player::set_job, "changeJobById");

		dukglue_register_method(ctx, &Player::set_map, "warp");
		dukglue_register_method(ctx, &Player::get_player, "getPlayer");

		dukglue_register_method(ctx, &Player::get_item_amount, "itemQuantity");
		dukglue_register_method(ctx, &Player::gain_item, "gainItem");
		dukglue_register_method(ctx, &Player::have_item, "haveItem");
		dukglue_register_method(ctx, &Player::can_hold, "canHold");
		dukglue_register_method(ctx, &Player::can_hold_one, "canHold");

		dukglue_register_method(ctx, &Player::set_map, "warp");

		dukglue_register_global(ctx, this, "cm");
		
	}

	//cout << mode << " " << type << " " << selection << endl;
	try {
		if (mode == 0) {
			if (duk_get_global_string(ctx, "start")) {
				if (duk_pcall(ctx, 0) != 0) {
					printf("Error: %s\n", duk_safe_to_string(ctx, -1));
				}
			}
		} else {
			if (duk_get_global_string(ctx, "action")) {
				dukglue_push(ctx, mode, type, selection);
				if (duk_pcall(ctx, 3) != 0) {
					printf("Error: %s\n", duk_safe_to_string(ctx, -1));
				}
			}
		}
	} catch (DukErrorException e) {
		cout << "ERROR : " <<  e.what() << endl;
	}

	//if (endChat) dispose();
}
