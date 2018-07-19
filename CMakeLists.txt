cmake_minimum_required(VERSION 2.6)
project(Simple_HFS)

add_subdirectory(./include)

add_compile_options(-std=c++11 -o3 -Wall -pedantic)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shfs main.cpp include/basic_fracs.tpp include/io.cpp include/cte.cpp include/cgwr.cpp)

install(TARGETS shfs RUNTIME DESTINATION bin)
