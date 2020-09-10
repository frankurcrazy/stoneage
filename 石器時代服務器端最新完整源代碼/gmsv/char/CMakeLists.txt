cmake_minimum_required(VERSION 3.10)
project(char)

add_library(char
char.c char_event.c char_data.c skill.c title.c
addressbook.c chatmagic.c event.c char_walk.c encount.c pet.c
enemy.c pet_event.c char_talk.c char_party.c char_item.c
chatroom.c petmail.c trade.c family.c char_angel.c char_base.c
)
target_include_directories(char PUBLIC ../include)
target_include_directories(char PUBLIC ../lua)
