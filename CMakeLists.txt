cmake_minimum_required(VERSION 3.17)
project(week3 C)

set(CMAKE_C_STANDARD 99)

add_executable(week3 main.c objects/queue.c objects/queue.h objects/list.c objects/list.h objects/objects.c objects/objects.h objects/list_queue.c objects/list_queue.h objects/sorts.c objects/sorts.h calunvier/tools.c calunvier/tools.h objects/char_search_tree.c objects/char_search_tree.h homeworks/supermarket.c homeworks/supermarket.h homeworks/array_supermarket.c homeworks/array_supermarket.h)