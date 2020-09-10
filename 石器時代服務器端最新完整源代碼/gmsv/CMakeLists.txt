cmake_minimum_required(VERSION 3.10)
project(gmsv)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
find_package(MySQL)
find_package(ZLIB)
add_subdirectory(mylua)
add_subdirectory(map)
add_subdirectory(char)
add_subdirectory(battle)
add_subdirectory(magic)
add_subdirectory(item)
add_subdirectory(npc)
add_subdirectory(npc_lua)
add_subdirectory(longzoro)

add_library(descrypt descrypt.c)
target_include_directories(descrypt PUBLIC include)

find_library(LUAJIT_LIB NAMES libluajit.a PATHS ${CMAKE_CURRENT_LIST_DIR}/lua REQUIRED NO_DEFAULT_PATH)
message("Got luajit lib:" ${LUAJIT_LIB})

add_library(lssproto lssproto_serv.c lssproto_util.c)
target_include_directories(lssproto PUBLIC include ${ZLIB_INCLUDE_DIRS})
target_include_directories(lssproto PUBLIC lua)
target_link_libraries(lssproto ${LUAJIT_LIB} ${ZLIB_LIBRARY})

add_library(saacproto saacproto_cli.c saacproto_util.c)
target_include_directories(saacproto PUBLIC include)
target_link_libraries(saacproto lssproto)

add_executable(gmsvjt 
	main.c
	autil.c
	buf.c
	callfromac.c
	callfromcli.c
	configfile.c
	const.c
	epollnet.c
	function.c
	handletime.c
	init.c
	link.c
	log.c
	md5.c
	msignal.c
	net.c
	object.c
	shop.c
	util.c)
target_include_directories(gmsvjt PUBLIC include)
target_include_directories(gmsvjt PUBLIC lua)
set(LINK_LIBS 
	char
	npc
	map
	item
	magic
	battle
	longzoro
	mylua
	npc_lua
	${LUAJIT_LIB}
	saacproto
	lssproto
	descrypt
	pthread
	dl
	m)
target_link_libraries(gmsvjt
	${LINK_LIBS} ${LINK_LIBS})
