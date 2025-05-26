#include "entity.hpp"

#include "gta/net_object_mgr.hpp"
#include "gta/gta_util.hpp"
#include "math.hpp"
#include "gta/script/natives.hpp"
#include "gta/packet.hpp"
#include "pools.hpp"
#include "gta/script/script.hpp"
#include "services/players/player_service.hpp"

#include <entities/CDynamicEntity.hpp>

namespace
{
	int get_next_token_value(int prev_token)
	{
		for (int i = 0; i < 0x1F; i++)
		{
			if ((i << 27) - (prev_token << 27) > 0)
				return i;
		}

		return 0;
	}
}

namespace big::entity
{
	bool network_has_control_of_entity(rage::netObject* net_object)
	{
		return !net_object || !net_object->m_is_remote && (net_object->m_wants_to_be_owner == -1);
	}

	bool take_control_of(Entity ent, int timeout)
	{
		if (!*g_pointers->m_is_session_started)
			return true;

		auto hnd = g_pointers->m_handle_to_ptr(ent);

		if (!hnd || !hnd->m_net_object)
			return false;

		if (hnd->m_entity_type != 3 && hnd->m_entity_type != 4 && hnd->m_entity_type != 5)
			return false;

		for (int i = 0; i <= timeout; ++i)
		{
			if (network_has_control_of_entity(hnd->m_net_object))
				return true;

			g_pointers->m_request_control(hnd->m_net_object);

			if (timeout != 0)
				script::get_current()->yield();
		}

		return false;
	}

	bool raycast(Entity* ent)
	{
		BOOL hit;
		Vector3 dontCare;

		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot       = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir       = math::rotation_to_direction(rot);
		Vector3 farCoords;

		farCoords.x = camCoords.x + dir.x * 1000;
		farCoords.y = camCoords.y + dir.y * 1000;
		farCoords.z = camCoords.z + dir.z * 1000;

		auto shape_test  = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x,
            camCoords.y,
            camCoords.z,
            farCoords.x,
            farCoords.y,
            farCoords.z,
            -1,
            0,
            7);
		auto test_result = SHAPETEST::GET_SHAPE_TEST_RESULT(shape_test, &hit, &dontCare, &dontCare, ent);

		return (test_result == 2 && hit == TRUE);
	}

	bool raycast(Vector3* endcoor)
	{
		Entity ent;
		BOOL hit;
		Vector3 surfaceNormal;

		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 dir       = math::rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(2));
		Vector3 farCoords;

		farCoords.x = camCoords.x + dir.x * 1000;
		farCoords.y = camCoords.y + dir.y * 1000;
		farCoords.z = camCoords.z + dir.z * 1000;

		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoords.x,
		    camCoords.y,
		    camCoords.z,
		    farCoords.x,
		    farCoords.y,
		    farCoords.z,
		    -1,
		    0,
		    7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, endcoor, &surfaceNormal, &ent);

		return (bool)hit;
	}

	bool load_ground_at_3dcoord(Vector3& location)
	{
		constexpr float max_ground_check = 1000.f;
		constexpr int max_attempts       = 300;
		float ground_z                   = location.z;
		int current_attempts             = 0;
		bool found_ground;
		float height;

		do
		{
			found_ground = MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, max_ground_check, &ground_z, FALSE, FALSE);
			STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, location.z);

			if (current_attempts % 10 == 0)
			{
				location.z += 25.f;
			}

			++current_attempts;

			script::get_current()->yield();
		} while (!found_ground && current_attempts < max_attempts);

		if (!found_ground)
		{
			return false;
		}

		if (WATER::GET_WATER_HEIGHT(location.x, location.y, location.z, &height))
		{
			location.z = height;
		}
		else
		{
			location.z = ground_z + 1.f;
		}

		return true;
	}

	bool request_model(rage::joaat_t hash)
	{
		if (STREAMING::HAS_MODEL_LOADED(hash))
		{
			return true;
		}

		bool has_loaded;

		if (STREAMING::IS_MODEL_VALID(hash) && STREAMING::IS_MODEL_IN_CDIMAGE(hash))
		{
			do
			{
				has_loaded = STREAMING::HAS_MODEL_LOADED(hash);
				if (has_loaded)
					break;

				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			} while (!has_loaded);

			return true;
		}

		return false;
	}

	double distance_to_middle_of_screen(const rage::fvector2& screen_pos)
	{
		double cumulative_distance{};

		if (screen_pos.x > 0.5)
			cumulative_distance += screen_pos.x - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.x;

		if (screen_pos.y > 0.5)
			cumulative_distance += screen_pos.y - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.y;

		return cumulative_distance;
	}

	void force_remove_network_entity(rage::CDynamicEntity* entity, player_ptr for_player, bool delete_locally)
	{
		if (!entity->m_net_object)
			return;

		force_remove_network_entity(entity->m_net_object->m_object_id, entity->m_net_object->m_ownership_token, for_player, delete_locally);
	}

	void force_remove_network_entity(std::uint16_t net_id, int ownership_token, player_ptr for_player, bool delete_locally)
	{
		char buf[0x200]{};
		rage::datBitBuffer remove_buf(buf, sizeof(buf));
		int msgs_written = 0;

		if (ownership_token != -1)
		{
			remove_buf.Write<std::uint16_t>(net_id, 13);
			remove_buf.Write<int>(get_next_token_value(ownership_token), 5);
			msgs_written++;
		}
		else
		{
			// try all tokens if we don't know it
			for (int i = 0; i < 0x1F; i++)
			{
				remove_buf.Write<std::uint16_t>(net_id, 13);
				remove_buf.Write<int>(i, 5);
				msgs_written++;
			}
		}

		packet pack;
		pack.write_message(rage::eNetMessage::MsgPackedReliables);
		pack.write<int>(4, 4); // remove
		pack.write<int>(msgs_written, 5);
		pack.write<int>(remove_buf.GetPosition(), 13);
		pack.m_buffer.WriteArray(&buf, remove_buf.GetPosition());

		if (for_player)
		{
			pack.send(for_player->get_net_game_player()->m_msg_id);
		}
		else
		{
			for (auto& player : g_player_service->players())
			{
				if (player.second->get_net_game_player())
				{
					if (!player.second->get_ped() || player.second->get_ped()->m_net_object->m_object_id != net_id) // would crash the player otherwise
					{
						pack.send(player.second->get_net_game_player()->m_msg_id);
					}
				}
			}
		}

		if (delete_locally)
			if (auto object = (*g_pointers->m_network_object_mgr)->find_object_by_id(net_id, true))
				(*g_pointers->m_network_object_mgr)->UnregisterNetworkObject(object, 8, true, true);
	}
}
