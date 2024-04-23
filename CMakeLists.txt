cmake_minimum_required(VERSION 3.28)
project(csi1430_The_Byte_Brigade_)

set(CMAKE_CXX_STANDARD 14)

include_directories(c++_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(csi1430_The_Byte_Brigade_
    c++_project/config.h
    c++_project/Game.cpp
    c++_project/Game.h
    c++_project/grid.cpp
    c++_project/grid.h
    c++_project/main.cpp
        c++_project/PLOTTER/SDL_Plotter.cpp
        c++_project/PLOTTER/SDL_Plotter.h
    c++_project/square.cpp
    c++_project/square.h
        c++_project/Entites/Headers/HumanFunc.h
        c++_project/Entites/Src/HumanFunc.cpp
)

target_link_libraries(csi1430_The_Byte_Brigade_ SDL2main SDL2 SDL2_mixer)