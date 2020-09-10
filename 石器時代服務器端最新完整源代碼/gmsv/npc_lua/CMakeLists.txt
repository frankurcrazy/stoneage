cmake_minimum_required(VERSION 3.10)
project(npc_lua)

add_library(npc_lua npc_lua.c npc_lua_ex.c npc_lua_item.c npc_lua_nlg.c npc_lua_nl.c npc_lua_obj.c npc_lua_char.c npc_lua_battle.c npc_lua_game.c npc_lua_map.c npc_lua_spell.c npc_lua_sql.c)
target_include_directories(npc_lua PUBLIC ../include)
target_include_directories(npc_lua PUBLIC ../lua)
