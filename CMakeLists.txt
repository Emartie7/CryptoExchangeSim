cmake_minimum_required(VERSION 3.24)
if(BUILD_GTEST)
    set(BinName "MerkleRex_Test")
else()
    set(BinName "MerkleRex")
endif()

project(${BinName})
project(${BinName} VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
option(BUILD_GTEST "Generate test binary instead of application." OFF)



if(BUILD_GTEST)
    include(FetchContent)
    include(GoogleTest)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    FetchContent_MakeAvailable(GoogleTest)
    enable_testing()
    #No "user-defined" main function, use GTest main.
    add_executable(${PROJECT_NAME} #test/MyTest.cpp 
                                   test/ObeMatch_Test.cpp
                                   test/WalletTest.cpp
                                   src/UserMenuIF/UserMenuIF.cpp 
                                   src/OrderBookLib/OrderBookLib.cpp 
                                   src/CsvReader/CsvReader.cpp
                                   src/OrderBookLib/OrderBook.cpp
                                   src/Wallet/Wallet.cpp) 
    target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock)
    gtest_discover_tests(${PROJECT_NAME})
else()
    #Use application "main"
    add_executable(${PROJECT_NAME} src/main.cpp 
                                   src/UserMenuIF/UserMenuIF.cpp 
                                   src/OrderBookLib/OrderBookLib.cpp 
                                   src/CsvReader/CsvReader.cpp
                                   src/OrderBookLib/OrderBook.cpp
                                   src/Wallet/Wallet.cpp) 
endif()
target_include_directories(${PROJECT_NAME} PUBLIC 
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/UserMenuIF
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/OrderBookLib
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/CsvReader
                           ${CMAKE_CURRENT_SOURCE_DIR}/src/Wallet)


