cmake_minimum_required(VERSION 3.22)
project(WeekendTracing)

set(CMAKE_CXX_STANDARD 20)

INCLUDE_DIRECTORIES(Src)

add_executable(WeekendTracing Src/main.cpp Src/Sphere.cpp)
