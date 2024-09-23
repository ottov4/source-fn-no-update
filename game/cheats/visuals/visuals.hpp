#pragma once
#include "../../../includes.hpp"
#include <iostream>               // For std::cout
#include <string>                 // For std::string
#include <unordered_map>          // For std::unordered_map]

void stroked_text(ImFont* font, float fontSize, ImVec2 position, ImColor color, const char* text)
{
	MASK
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x - 1, position.y - 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x + 1, position.y - 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x - 1, position.y + 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, ImVec2(position.x + 1, position.y + 1), ImColor(0, 0, 0), text);
	ImGui::GetForegroundDrawList()->AddText(font, fontSize, position, color, text);
}

void draw_box(int x, int y, int w, int h, const ImColor color)
{
	MASK
	//ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(0, 0, 0, 50), 0, 0);
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x + 1, y + 1), ImVec2(x + w - 1, y + h - 1), ImColor(0, 0, 0), 0, 0, 1.0f);
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0), 0, 0, 1.0f);
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x + 1, y - 1), ImVec2(x + w - 1, y + h + 1), ImColor(0, 0, 0), 0, 0, 1.0f);
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x - 1, y + 1), ImVec2(x + w + 1, y + h - 1), ImColor(0, 0, 0), 0, 0, 1.0f);
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0, 1.0f);
}

static void draw_corner_box(float x, float y, float w, float h, ImColor color)
{
	MASK
	//ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(0, 0, 0, 100), 0, 0);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x - 1, y - 1), ImVec2(x - 1, y + (h / 3) - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x - 1, y - 1), ImVec2(x + (w / 3) - 1, y - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3) + 1, y - 1), ImVec2(x + w + 1, y - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w + 1, y - 1), ImVec2(x + w + 1, y + (h / 3) - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x - 1, y + h - (h / 3) + 1), ImVec2(x - 1, y + h + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x - 1, y + h + 1), ImVec2(x + (w / 3) - 1, y + h + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3) + 1, y + h + 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w + 1, y + h - (h / 3) + 1), ImVec2(x + w + 1, y + h + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + 1, y + 1), ImVec2(x + 1, y + (h / 3) + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + 1, y + 1), ImVec2(x + (w / 3) + 1, y + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3) - 1, y + 1), ImVec2(x + w - 1, y + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - 1, y + 1), ImVec2(x + w - 1, y + (h / 3) + 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + 1, y + h - (h / 3) - 1), ImVec2(x + 1, y + h - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + 1, y + h - 1), ImVec2(x + (w / 3) + 1, y + h - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3) - 1, y + h - 1), ImVec2(x + w - 1, y + h - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - 1, y + h - (h / 3) - 1), ImVec2(x + w - 1, y + h - 1), ImColor(0, 0, 0), 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), color, 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), color, 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), color, 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), color, 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), color, 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), color, 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), color, 1.0f);
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), color, 1.0f);
}

struct Fortnite
{
	// Enum to represent different actor types in the game
	enum ActorType
	{
		NOT_IN_USE = 0,
		CHEST = 1,
		AMMO_BOX = 2,
	};

	// Struct to define actor properties
	struct ActorDefinitions
	{
		int actorID;           // Actor ID
		std::string fname;     // Actor name
		ActorType actorType;   // Actor type
	};

	// Static method to return a map of actor names to actor types
	static const std::unordered_map<std::string, ActorType>& GetActorByName()
	{
		// Static map to store the association between actor names and their types
		static const std::unordered_map<std::string, ActorType> actorMap = {
			{"Tiered_Chest", CHEST},
			{"Tiered_Ammo", AMMO_BOX},
			// Add more actors as needed
		};

		return actorMap;
	}
};
void GetActorLocations()
{
	auto levels = read<TArray<uintptr_t>>(GWORLD + levelssss); // I FUCKING DONE NO LOOT ESP
	if (!levels.is_valid())
		return;

	//for (size_t i = 0; i < levels.length(); ++i) {
	//	uintptr_t levelAddress = levels[i];
}

void actorLoop()
{
	MASK
	__int64 va_text = 0;
	for (int i = 0; i < 25; i++)
	{
		if (read<__int32>(virtualaddy + (i * 0x1000) + 0x250) == 0x260E020B)
		{
			va_text = virtualaddy + ((i + 1) * 0x1000);
		}
	}
	cache::gworld = read<uintptr_t>(GWORLD + va_text);
	if (!cache::gworld) return;

	cache::game_instance = read<uintptr_t>(cache::gworld + GAME_INSTANCE);
	if (!cache::game_instance) return;

	cache::local_players = read<uintptr_t>(read<uintptr_t>(cache::game_instance + LOCAL_PLAYERS));
	if (!cache::local_players) return;

	cache::player_controller = read<uintptr_t>(cache::local_players + PLAYER_CONTROLLER);
	if (!cache::player_controller) return;

	cache::game_state = read<uintptr_t>(cache::gworld + GAME_STATE);
	if (!cache::game_state) return;

	cache::local_pawn = read<uintptr_t>(cache::player_controller + LOCAL_PAWN);
	if (!cache::local_pawn) return;

	cache::persistent_level = read<uintptr_t>(cache::gworld + PERSISTENT_LEVEL);
	if (!cache::persistent_level) return;

	cache::root_component = read<uintptr_t>(cache::local_pawn + ROOT_COMPONENT);
	if (!cache::root_component) return;

	cache::player_state = read<uintptr_t>(cache::local_pawn + PLAYER_STATE);
	if (!cache::player_state) return;

	cache::current_weapon = read<uintptr_t>(cache::local_pawn + CURRENT_WEAPON);
	if (!cache::current_weapon) return;

	cache::localRelativeLocation = read<Vector3>(cache::root_component + RELATIVE_LOCATION);
	cache::closest_distance = FLT_MAX;
	cache::closest_mesh = NULL;

	uintptr_t game_state = read<uintptr_t>(cache::gworld + GAME_STATE);
	if (!game_state) return;

	uintptr_t player_array = read<uintptr_t>(game_state + PLAYER_ARRAY);
	uintptr_t player_count = read<int>(game_state + (PLAYER_ARRAY + sizeof(uintptr_t)));

	for (int i = 0; i < player_count; i++)
	{
		uintptr_t player_state = read<uintptr_t>(player_array + (i * sizeof(uintptr_t)));
		if (!player_state) continue;

		uintptr_t pawn_private = read<uintptr_t>(player_state + PAWN_PRIVATE);
		if (!pawn_private) continue;
		if (pawn_private == cache::local_pawn) continue;

		uintptr_t mesh = read<uintptr_t>(pawn_private + MESH);
		if (!mesh) continue;

		uintptr_t actorRootComponent = read<uintptr_t>(pawn_private + ROOT_COMPONENT);
		Vector3 actorRelativeLocation = read<Vector3>(actorRootComponent + RELATIVE_LOCATION);
		float distance = cache::localRelativeLocation.distance(actorRelativeLocation) / 100.0f;

		Vector3 head3d = get_entity_bone(mesh, 110);
		Vector2 head2d = project_world_to_screen(head3d);
		Vector3 bottom3d = get_entity_bone(mesh, 0);
		Vector2 bottom2d = project_world_to_screen(bottom3d);
		Vector2 boxHead = project_world_to_screen(Vector3(head3d.x, head3d.y, head3d.z + 20.0f));
		float box_height = abs(boxHead.y - bottom2d.y);
		float box_width = box_height * 0.50f;

			if (!cache::local_pawn)
			{
				// settings::visuals::distance = 2400;
			}
			if (settings::visuals::enable)
			{
				if (settings::visuals::radar)
				{
					//if (distance <= 100.0f)
					//{
					//	Vector2 radarPos = worldToRadar(actorRelativeLocation, cache::localRelativeLocation, cache::local_camera.rotation, 200);
					//	cache::radarPoints.push_back(ImVec2(radarPos.x, radarPos.y));
					//}
				}

				if (distance <= settings::visuals::renderDistance)
				{
					if (settings::visuals::box)
					{
						switch (settings::visuals::boxType)
						{
						case boxType::normal:
						{
							if (is_visible(mesh))
							{
								draw_box(boxHead.x - (box_width / 2), boxHead.y, box_width, box_height, settings::colors::icBoxColorVisible);
							}
							else
							{
								draw_box(boxHead.x - (box_width / 2), boxHead.y, box_width, box_height, settings::colors::icBoxColorInvisible);
							}
							break;
						}
						case boxType::corner:
						{
							if (is_visible(mesh))
							{
								draw_corner_box(boxHead.x - (box_width / 2), boxHead.y, box_width, box_height, settings::colors::icBoxColorVisible);
							}
							else
							{
								draw_corner_box(boxHead.x - (box_width / 2), boxHead.y, box_width, box_height, settings::colors::icBoxColorInvisible);
							}
							break;
						}
						}
					}

					if (settings::visuals::skeleton)
					{
						for (int i = 0; i < sizeof(boneConnections) / sizeof(boneConnections[0]); i++)
						{
							int bone1 = boneConnections[i].bone1;
							int bone2 = boneConnections[i].bone2;
							Vector3 vectorBone1 = get_entity_bone(mesh, bone1);
							Vector3 vectorBone2 = get_entity_bone(mesh, bone2);
							Vector2 wtsBone1 = project_world_to_screen(vectorBone1);
							Vector2 wtsBone2 = project_world_to_screen(vectorBone2);

							if (is_visible(mesh))
							{
								ImGui::GetForegroundDrawList()->AddLine(ImVec2(wtsBone1.x, wtsBone1.y), ImVec2(wtsBone2.x, wtsBone2.y), ImColor(0, 0, 0), 2.0f);
								ImGui::GetForegroundDrawList()->AddLine(ImVec2(wtsBone1.x, wtsBone1.y), ImVec2(wtsBone2.x, wtsBone2.y), settings::colors::icSkeletonColorVisible, 1);
							}
							else
							{
								ImGui::GetForegroundDrawList()->AddLine(ImVec2(wtsBone1.x, wtsBone1.y), ImVec2(wtsBone2.x, wtsBone2.y), ImColor(0, 0, 0), 2.0f);
								ImGui::GetForegroundDrawList()->AddLine(ImVec2(wtsBone1.x, wtsBone1.y), ImVec2(wtsBone2.x, wtsBone2.y), settings::colors::icSkeletonColorInvisible, 1);
							}
						}
					}

					if (settings::visuals::line)
					{
						if (is_visible(mesh))
						{
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(settings::screen_center_x, settings::height), ImVec2(bottom2d.x, bottom2d.y), settings::colors::icTracerColorVisible, 1.0f);
						}
						else
						{
							ImGui::GetForegroundDrawList()->AddLine(ImVec2(settings::screen_center_x, settings::height), ImVec2(bottom2d.x, bottom2d.y), settings::colors::icTracerColorInvisible, 1.0f);
						}
					}

					if (settings::visuals::name)
					{
						std::string playerUsername = getUsername(player_state);

						ImVec2 textSize = ImGui::CalcTextSize(playerUsername.c_str());
						stroked_text(ImGui::GetFont(), 13.0f, ImVec2(boxHead.x - textSize.x / 2, boxHead.y - 10 - textSize.y / 2), ImColor(255, 255, 255), playerUsername.c_str());
					}

					if (settings::visuals::platform)
					{
						uintptr_t platformPtr = read<uintptr_t>(player_state + PLATFORM);
						wchar_t platformChar[64] = { 0 };
						PaysonDRV::ReadPhysicalMemory(reinterpret_cast<PVOID>(platformPtr), reinterpret_cast<uint8_t*>(platformChar), sizeof(platformChar));
						std::wstring platformWstr(platformChar);
						std::string platformStr(platformWstr.begin(), platformWstr.end());

						ImVec2 textSize = ImGui::CalcTextSize(platformStr.c_str());
						if (settings::visuals::name)
						{
							stroked_text(ImGui::GetFont(), 13.0f, ImVec2(boxHead.x - textSize.x / 2, boxHead.y - 25 - textSize.y / 2), ImColor(255, 255, 255), platformStr.c_str());
						}
						else
						{
							stroked_text(ImGui::GetFont(), 13.0f, ImVec2(boxHead.x - textSize.x / 2, boxHead.y - 10 - textSize.y / 2), ImColor(255, 255, 255), platformStr.c_str());
						}
					}

					if (settings::visuals::distance)
					{
						char dist[64];
						sprintf_s(dist, "%.fm", distance);

						ImVec2 textSize = ImGui::CalcTextSize(dist);
						stroked_text(ImGui::GetFont(), 13.0f, ImVec2(bottom2d.x - textSize.x / 2, bottom2d.y + 10 - textSize.y / 2), ImColor(255, 255, 255), dist);
					}

					if (settings::visuals::rank)
					{
						uintptr_t habaneroComponent = read<uintptr_t>(player_state + HABANERO_COMPONENT);
						uint32_t rank = read<uint32_t>(habaneroComponent + RANKED_PROGRESS + 0x10);
						std::string rankName = getRank(rank);

						ImVec2 textSize = ImGui::CalcTextSize(rankName.c_str());
						if (settings::visuals::distance)
						{
							stroked_text(ImGui::GetFont(), 13.0f, ImVec2(bottom2d.x - textSize.x / 2, bottom2d.y + 25 - textSize.y / 2), ImColor(255, 255, 255), rankName.c_str());
						}
						else
						{
							stroked_text(ImGui::GetFont(), 13.0f, ImVec2(bottom2d.x - textSize.x / 2, bottom2d.y + 10 - textSize.y / 2), ImColor(255, 255, 255), rankName.c_str());
						}
					}
				}
			}

		bool fovreset;
		bool magicreset;

		if (settings::exploits::fovchanger)
		{
			MASK
			fovreset = false;
			write<float>(cache::player_controller + 0x2758, settings::exploits::fovchanger_value); // https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerController&member=FOVMinimum
			write<float>(cache::player_controller + 0x275C, settings::exploits::fovchanger_value); // FOVMaximum
		}
		else if (!fovreset)
		{
			MASK
			write<float>(cache::player_controller + 0x2758, settings::exploits::fovchanger_value); // FOVMinimum
			write<float>(cache::player_controller + 0x275C, settings::exploits::fovchanger_value); // FOVMaximum
			fovreset = true;
		}

		if (settings::exploits::magicbullet)
		{
			MASK
			magicreset = false;
			auto weapon = read<uintptr_t>(cache::local_pawn + CURRENT_WEAPON);

			write<bool>(weapon + 0xe51, true);  // 0xe51 or 0x3f8  bTraceThroughWorld
			write<int32_t>(weapon + 0xea8, 0);  // TraceThroughPawnsLimit

			write<int32_t>(weapon + 0xeac, 1000);  // TraceThroughBuildingsLimit
			write<int32_t>(weapon + 0xeb0, 1000);  // TraceThroughLandscapeLimit
		}
		else if (!magicreset)
		{
			MASK
			auto weapon = read<uintptr_t>(cache::local_pawn + CURRENT_WEAPON);

			write<bool>(weapon + 0xe51, false); // bTraceThroughWorld
			write<int32_t>(weapon + 0xea8, 0);  // TraceThroughPawnsLimit
			write<int32_t>(weapon + 0xeac, 0);  // TraceThroughBuildingsLimit
			write<int32_t>(weapon + 0xeb0, 0);  // TraceThroughLandscapeLimit
			magicreset = true;
		}

		if (settings::exploits::aimwhilejumping)
		{
			MASK
			write<bool>(cache::local_pawn + 0x5659, true);  // bTraceThroughWorld //https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerPawnAthena&member=bADSWhileNotOnGround
		}
		else
		{ 
			MASK
			write<bool>(cache::local_pawn + 0x5659, false);  // bTraceThroughWorld //https://dumpspace.spuckwaffel.com/Games/?hash=6b77eceb&type=classes&idx=AFortPlayerPawnAthena&member=bADSWhileNotOnGround
		}

		if (settings::exploits::spinbot)
		{
			MASK
			auto Mesh = read<uint64_t>(cache::local_pawn + MESH);
			static auto Cached = read<Vector3>(Mesh + 0x140);

			if (GetAsyncKeyState(VK_LBUTTON)) {
				write<Vector3>(Mesh + 0x140, Vector3(1, rand() % 361, 1));
			}
			else write<Vector3>(Mesh + 0x140, Cached);
		}

		if (settings::exploits::overheat)
		{
			MASK
			float TimeHeatWasLastAdded = read<float>(cache::local_pawn + 0x1c9c);
			float TimeOverheatedBegan = read<float>(cache::local_pawn + 0x1ca0);
			float OverheatValue = read<float>(cache::local_pawn + 0x1c94);
			float WeaponOverheatedAnimation = read<float>(cache::local_pawn + 0x1c88);
			uintptr_t CurrentWeapon = read<float>(cache::local_pawn + 0xA68);

			if (TimeHeatWasLastAdded != 0.f or TimeOverheatedBegan != 0.f or OverheatValue != 0.f or WeaponOverheatedAnimation != 0.f) {
				write<float>(CurrentWeapon + 0x14d4, 0.f);
				write<float>(CurrentWeapon + 0x14d8, 0.f);
				write<float>(CurrentWeapon + 0x14cc, 0.f);
				write<float>(CurrentWeapon + 0x14c0, 0.f);
			}
		}

		if (settings::exploits::noreload)
		{
			MASK
			uintptr_t worldsettings = read<uint64_t>(cache::persistent_level + 0x30);
			uintptr_t CurrentWeapon = read<uintptr_t>(cache::local_pawn + 0x338);
			uintptr_t SimcraftsTwoPoint5Hours1 = read<uintptr_t>(cache::current_weapon + 0xA68);
			uintptr_t SimcraftsTwoPoint5Hours2 = read<uintptr_t>(SimcraftsTwoPoint5Hours1 + 0x1678);
			uintptr_t SimcraftsTwoPoint5Hours3 = read<uintptr_t>(SimcraftsTwoPoint5Hours2 + 0x6233);
			uintptr_t SimcraftsTwoPoint5Hours4 = read<uintptr_t>(SimcraftsTwoPoint5Hours3 + 0xc87);
			uintptr_t SimcraftsTwoPoint5Hours5 = read<uintptr_t>(SimcraftsTwoPoint5Hours4 + 0xb39);
			uintptr_t SimcraftsTwoPoint5Hours6 = read<uintptr_t>(SimcraftsTwoPoint5Hours5 + 0x267);
			uintptr_t SimcraftsTwoPoint5Hours7 = read<uintptr_t>(SimcraftsTwoPoint5Hours6 + 0x5cc);
			uintptr_t SimcraftsTwoPoint5Hours8 = read<uintptr_t>(SimcraftsTwoPoint5Hours7 + 0xc82 + 0x8 + 0x18);

			write<char>(SimcraftsTwoPoint5Hours8 + 0x9c8, 0);
			write<float>(SimcraftsTwoPoint5Hours8 + 0x928, 0.01);

			bool cum = read<bool>(CurrentWeapon + 0x329);

			if (cum) {
				write<float>(worldsettings + 0x3C0, 70);
			}
			else {
				write<float>(worldsettings + 0x3C0, 1);
			}
		}

		if (settings::exploits::carfly)
		{
			MASK
			uintptr_t CurrentVehicle = read<DWORD_PTR>(cache::local_pawn + 0x2a18); // CurrentVehicle

			if (CurrentVehicle && GetAsyncKeyState(VK_SPACE))
			{
				write<bool>(CurrentVehicle + 0x87a, false); // bUseGravity : 1
			}
			else {
				write<bool>(CurrentVehicle + 0x87a, true); // bUseGravity : 1
			}

		}

		auto dist = getCrossDistance(head2d.x, head2d.y, settings::width / 2, settings::height / 2);
		if (dist <= settings::aimbot::fov && dist < cache::closest_distance)
		{
			cache::closest_distance = dist;
			cache::closest_mesh = mesh;
		}
	}
}
