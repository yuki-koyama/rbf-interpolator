cmake_minimum_required(VERSION 3.1)

find_package(Eigen3 REQUIRED)
find_package(Qt5 COMPONENTS OpenGL Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/rbf_interpolator_core)

file(GLOB files *.cpp *.h)
add_executable(rbf_interpolator_test ${files})
target_link_libraries(rbf_interpolator_test Qt5::Widgets rbf_interpolator_core)
