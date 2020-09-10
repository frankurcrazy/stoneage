cmake_minimum_required(VERSION 3.10)
project(longzoro)

add_library(longzoro
	characters.c
	crypto.c
	luckstar.c
	move.c
	newshop.c
	playerquestion.c
	sasql_linux.c
)
target_include_directories(longzoro PUBLIC ../include)
target_include_directories(longzoro PUBLIC ../lua)
target_link_libraries(longzoro char ${MYSQL_LIBRARY})
