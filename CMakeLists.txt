
cmake_minimum_required(VERSION 3.0)
project(P_Name)
set(CMAKE_CXX_STANDARD 11)
set(SOURCES
    src/main.cpp
    src/app.cpp    
)
include_directories(include/)
add_executable(app )
target_link_libraries(app sfml-window sfml-system sfml-graphics)
