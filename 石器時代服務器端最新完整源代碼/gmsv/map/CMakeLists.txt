cmake_minimum_required(VERSION 3.10)
project(map)

add_library(map map_deal.c map_util.c map_warppoint.c readmap.c)
target_include_directories(map PUBLIC ../include)
target_include_directories(map PUBLIC ../lua)
