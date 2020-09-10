cmake_minimum_required(VERSION 3.10)

add_library(magic magic.c magic_base.c magic_field.c)
target_include_directories(magic PUBLIC ../include)
target_include_directories(magic PUBLIC ../lua)
