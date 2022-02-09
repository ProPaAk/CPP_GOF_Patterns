cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

project (${ProjectId})

add_executable(${ProjectId} 
	Bomb.h	
	Bomb.cpp
    DestroyableGroundObject.h
    DynamicObject.h
    GameObject.h
    Ground.h
    Ground.cpp
    House.h
    House.cpp
    LevelGUI.h
    LevelGUI.cpp
    MyTools.h
    MyTools.cpp
    Plane.h
    Plane.cpp
    SBomber.h
    SBomber.cpp
    SBomberProject.cpp
    Tank.h
    Tank.cpp
)