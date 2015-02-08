find_package(GTest)
find_package(GMock)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Eigen_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

# gather all *.h and *.cpp files
file(GLOB SRC *.h *.cpp)

add_executable(UnitTests ${SRC})
target_link_libraries(UnitTests ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} LifeUniversalis)
