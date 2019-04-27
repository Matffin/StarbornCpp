cmake_minimum_required(VERSION 3.13)
project(Starborn_02)

set(CMAKE_CXX_STANDARD 17)

#get sfml
set(SFML_DIR "E:/02_Dateien/05. GAME Projects/00. University/C++Game/03_ SFML_Stuff/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit/SFML-2.5.1/lib/cmake/SFML")

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
include_directories(${PROJECT_SOURCE_DIR} Library) #Library/ThirdParty/log4cplus/ Library/ECS/include/ECS)

#FILE(GLOB_RECURSE ECSFILES Library/ECS/ *.h)
#FILE(GLOB_RECURSE ECSFILES
#        Library/ECS/src/ *.cpp
#        Library/ECS/src/Event/ *.cpp
#        Library/ECS/src/Log/ *.cpp
#        Library/ECS/src/Memory/Allocator/ *.cpp
#        Library/ECS/src/Memory/ *.cpp
#        Library/ECS/src/util/ *.cpp
#        )

set(EXECUTABLE_NAME "Starborn")
set(SOURCE_FILES main.cpp
        Library/Core/Draw.cpp
        Library/Core/Game.cpp
        Library/Core/Input.cpp
        Library/Core/Update.cpp
        Library/TextureManager/TextureHolder.cpp
        Library/Stars/StarManager.cpp
        Library/M/ManagerM.cpp
        Library/Galaxy/GalaxyBackground.cpp)

#set(HEADER_FILES Library/Utility/Utilities.h Library/Utility/RandomGenerator.h Library/Utility/Helpers.h Library/TextureManager/TextureHolder.h Library/TextureManager/TextureHolder.cpp Library/Core/Game.h Library/Core/Game.cpp Library/Core/Input.cpp Library/Core/Update.cpp Library/Core/Draw.cpp)

#need to fix for target i think
#target_include_directories(${EXECUTABLE_NAME} Library)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Content/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Content/)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES} ${ECSFILES})

# Detect and add SFML
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2.5.1 REQUIRED network audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif ()