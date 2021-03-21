project(provinces)

cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
set(sources 
	src/main.cpp 
	src/board.cpp
	src/turn.cpp
	src/institution.cpp
    src/FactionRoutine.cpp
    src/action.cpp
    src/faction_relation.cpp
	)
add_executable( provinces ${sources})
