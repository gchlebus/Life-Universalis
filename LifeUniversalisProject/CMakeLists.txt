cmake_minimum_required(VERSION 2.6)

project(LifeUniversalis)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# libraries set up
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.57.0 COMPONENTS chrono thread date_time system timer)
set(Eigen_INCLUDE_DIRS "usr/local/include" CACHE PATH "eigen include dirs")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add child projects
add_subdirectory(LifeUniversalis)
add_subdirectory(LifeUniversalisTest)
