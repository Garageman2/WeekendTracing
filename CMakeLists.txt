cmake_minimum_required(VERSION 3.22)
project(WeekendTracing)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

find_package(OpenGL REQUIRED)

add_subdirectory(Vendor/GLFW)

INCLUDE_DIRECTORIES(Src Vendor/STBImage/ Vendor/GLFW/include/GLFW/)

add_executable(WeekendTracing Src/main.cpp Src/Sphere.cpp Src/Hittable.cpp Src/HittableList.cpp Src/Camera.cpp)

target_link_libraries(WeekendTracing glfw)