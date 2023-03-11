cmake_minimum_required(VERSION 2.8.3)
project(gtkmm_ex)

set(EIGEN3_INCLUDE_DIR /usr/local/include/eigen3)

# find GTKMM
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(include ${GTKMM_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(gtkmm_ex src/main.cpp)
target_link_libraries(gtkmm_ex ${GTKMM_LIBRARIES})

