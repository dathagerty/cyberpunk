cmake_minimum_required(VERSION 3.0)
project(cyberpunk)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()
if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

set(SOURCES src/Actor.hpp src/Actor.cpp src/Ai.hpp src/Ai.cpp src/Attacker.hpp src/Attacker.cpp src/Container.hpp src/Container.cpp src/Destructible.hpp src/Destructible.cpp src/Engine.hpp src/Engine.cpp src/Gui.hpp src/Gui.cpp src/main.hpp src/main.cpp src/Map.hpp src/Map.cpp src/Pickable.hpp src/Pickable.cpp terminal.png)

include_directories(include)
link_directories(lib)

add_executable(cyberpunk MACOSX_BUNDLE ${SOURCES} )
