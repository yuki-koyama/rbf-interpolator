cmake_minimum_required(VERSION 3.1)

project(rbf_interpolator)

find_package(Qt5 COMPONENTS OpenGL Widgets)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(rbf_interpolator)
if(Qt5_FOUND)
	add_subdirectory(demos/test_2d_gui)
endif()
