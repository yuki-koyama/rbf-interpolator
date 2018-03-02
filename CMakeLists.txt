cmake_minimum_required(VERSION 3.1)

project(rbf_interpolator)

find_package(Qt5 COMPONENTS OpenGL Widgets)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(rbf_interpolator_core)
if(Qt5_FOUND)
	add_subdirectory(rbf_interpolator_test)
endif()
