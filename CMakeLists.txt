cmake_minimum_required(VERSION 3.20)
project(spicerack)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall -Wextra -Werror")
add_executable(spicerack
	andgate.h andgate.c
	clock.h clock.c
	counter.h counter.c
	main.c
	output.h output.c
	signal.h signal.c
	signalvalue.h signalvalue.c)
