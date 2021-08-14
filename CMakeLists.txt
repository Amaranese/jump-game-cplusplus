cmake_minimum_required(VERSION 3.6)
project(Jump)

#set(CMAKE_VERBOSE_MAKEFILE  true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    source/game/states/LevelState.cpp
    source/game/states/LevelState.hpp
    source/game/states/StartupState.cpp
    source/game/states/StartupState.hpp
    source/game/Game.cpp
    source/game/Game.hpp
    source/game/GameState.cpp
    source/game/GameState.hpp
    source/game/GameStateManager.cpp
    source/game/GameStateManager.hpp
    source/input/sdl2/Sdl2InputManager.cpp
    source/input/sdl2/Sdl2InputManager.hpp
    source/input/InputButton.hpp
    source/input/InputListener.hpp
    source/input/InputManager.cpp
    source/input/InputManager.hpp
    source/level/entities/Player.cpp
    source/level/entities/Player.hpp
    source/level/Block.cpp
    source/level/Block.hpp
    source/level/Entity.cpp
    source/level/Entity.hpp
    source/level/Layer.cpp
    source/level/Layer.hpp
    source/level/Level.cpp
    source/level/Level.hpp
    source/test/TestLevels.hpp
    source/test/TestLevels.cpp
    source/util/Util.hpp
    source/video/sdl2/Sdl2VideoManager.cpp
    source/video/sdl2/Sdl2VideoManager.hpp
    source/video/VideoManager.hpp
    source/Main.cpp)

add_executable(Jump ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(Jump ${SDL2_LIBRARY} ${OPENGL_LIBRARIES})
