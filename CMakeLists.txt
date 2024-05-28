cmake_minimum_required(VERSION 3.24)
project(MerkleRex)
project(MerkleRex VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# include(FetchContent)
# include(GoogleTest)
# FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
# FetchContent_MakeAvailable(GoogleTest)
# enable_testing()


add_executable(MerkleRex src/main.cpp src/UserMenuIF/UserMenuIF.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/UserMenuIF)

# target_link_libraries(MerkleRex GTest::gtest_main)


# gtest_discover_tests(MerkleRex)


