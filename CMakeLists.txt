cmake_minimum_required(VERSION 3.20)
project(spicerack)
add_executable(spicerack
	andgate.h andgate.c
	clock.h clock.c
	main.c
	signal.h signal.c)
