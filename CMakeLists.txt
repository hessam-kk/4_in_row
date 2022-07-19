
cmake_minimum_required(VERSION 3.0)
project(P_Name)
set(CMAKE_CXX_STANDARD 11)
set(SOURCES
    src/board.cpp
    src/main.cpp
    src/app.cpp 
    src/login.cpp
)
include_directories(include/)
add_executable(app ${SOURCES})
target_link_libraries(app sfml-window sfml-system sfml-graphics)
