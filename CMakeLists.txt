cmake_minimum_required(VERSION 3.20)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

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
    HouseBuilderA.h
    HouseBuilderA.cpp
    HouseBuilder.h
    LevelGUI.h
    LevelGUI.cpp
    MyTools.h
    MyTools.cpp
    Plane.h
    Plane.cpp
    SBomber.h
    SBomber.cpp
    SBomberProject.cpp
    TankAdapter.h
    TankAdapter.cpp
    TankAdaptee.h
    TankAdaptee.cpp
    Tank.h
    Tank.cpp
    BuilderDirector.h
)