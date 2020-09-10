cmake_minimum_required(VERSION 3.10)
project(battle)

add_library(battle
	battle.c
	battle_ai.c
	battle_command.c
	battle_event.c
	battle_item.c
	battle_magic.c
	pet_skill.c
	profession_skill.c)

target_include_directories(battle PUBLIC ../include)
target_include_directories(battle PUBLIC ../lua)
