cmake_minimum_required(VERSION 3.10)
project(item)

add_library(item
	item.c
	item_event.c
	item_gen.c
)
target_include_directories(item PUBLIC ../include)
target_include_directories(item PUBLIC ../lua)
