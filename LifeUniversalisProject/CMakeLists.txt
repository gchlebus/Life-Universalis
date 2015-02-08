cmake_minimum_required(VERSION 2.6)

project(LifeUniversalis)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# libraries set up
find_package(Boost 1.57.0 COMPONENTS thread timer system date_time)
set(Eigen_INCLUDE_DIRS "usr/local/include" CACHE PATH "eigen include dirs")

# add child projects
add_subdirectory(LifeUniversalis)
add_subdirectory(LifeUniversalisTest)
