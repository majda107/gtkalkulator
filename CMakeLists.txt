cmake_minimum_required(VERSION 3.17)
project(gtkalkulator)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(GLIB glib-2.0 REQUIRED)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

set(SOURCE_FILES main.cpp CalculatorWindow.cpp CalculatorWindow.h)
add_executable(gtkalkulator ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GTKMM_LIBRARIES})