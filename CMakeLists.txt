cmake_minimum_required(VERSION 2.8)

project(yobatronika)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory!" )
endif()

find_package(PkgConfig REQUIRED)
if(NOT PKGCONFIG_FOUND)
    message(SEND_ERROR "Failed to find PkgConfig")
    return()
else()
    pkg_check_modules (SDL2 REQUIRED sdl2)
    include_directories(${SDL2_INCLUDE_DIRS})
    message(STATUS "include: ${SDL2_INCLUDE_DIRS}")
    link_directories( ${SDL2_LIBRARY_DIRS} )

    pkg_check_modules (SDL2_IMAGE REQUIRED SDL2_image)
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
    message(STATUS "include: ${SDL2_IMAGE_INCLUDE_DIRS}")
    link_directories( ${SDL2_IMAGE_LIBRARY_DIRS} )
endif()

set(ALL_LIBS ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

include_directories("include")
set(HEADERS
"include/Game.h"
"include/TextureManager.h"
"include/GameObject.h"
"include/Player.h"
"include/Enemy.h"
"include/LoaderParams.h"
"include/SDLGameObject.h"
"include/Vector2D.h"
"include/InputHandler.h"
"include/MainApplication.h"
"include/GameState.h"
"include/MenuState.h"
"include/PlayState.h"
"include/GameStateMachine.h"
"include/MenuButton.h"
)

set(SOURCES
"src/main.cpp"
"src/Game.cpp"
"src/TextureManager.cpp"
"src/Player.cpp"
"src/Enemy.cpp"
"src/LoaderParams.cpp"
"src/SDLGameObject.cpp"
"src/Vector2D.cpp"
"src/InputHandler.cpp"
"src/MainApplication.cpp"
"src/MenuState.cpp"
"src/PlayState.cpp"
"src/GameStateMachine.cpp"
"src/MenuButton.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})

# Xcode
set_target_properties(${PROJECT_NAME} PROPERTIES 
                      XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/")


