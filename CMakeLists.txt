cmake_minimum_required(VERSION 3.22)
project(WeekendTracing)

set(CMAKE_CXX_STANDARD 11)

set( CMAKE_BUILD_TYPE Debug )

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

find_package(OpenGL REQUIRED)

add_subdirectory(Vendor/GLFW)
add_subdirectory(Vendor/GLAD)


INCLUDE_DIRECTORIES(Src Vendor/STBImage/ Vendor/GLFW/include/GLFW/ Vendor/IMGui/)

add_executable(WeekendTracing Src/main.cpp Src/Sphere.cpp Src/Hittable.cpp Src/HittableList.cpp Src/Camera.cpp
        Vendor/IMGui/imgui.cpp
        Vendor/IMGui/imgui.h
        Vendor/IMGui/imgui_demo.cpp
        Vendor/IMGui/imgui_draw.cpp
        Vendor/IMGui/imgui_impl_glfw.cpp
        Vendor/IMGui/imgui_impl_glfw.h
        Vendor/IMGui/imgui_impl_opengl3.cpp
        Vendor/IMGui/imgui_impl_opengl3.h
        Vendor/IMGui/imgui_internal.h
        Vendor/IMGui/imgui_tables.cpp
        Vendor/IMGui/imgui_widgets.cpp
        Vendor/IMGui/imstb_rectpack.h
        Vendor/IMGui/imstb_textedit.h
        Vendor/IMGui/imstb_truetype.h
        Vendor/IMGui/imgui_impl_opengl3_loader.h
        Src/RT.cpp
        )

target_link_libraries(WeekendTracing glfw)
target_link_libraries(WeekendTracing glad)