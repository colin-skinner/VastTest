cmake_minimum_required(VERSION 3.10)
project(VastTakeHome)
project(test_sim)

# Use clang++ as the compiler
# set(CMAKE_CXX_COMPILER clang++)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# gtest
Include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Add main

SET(TARGET_H
    Simulation.h  
    SimObject.h
   )

SET(TARGET_SRC
    main.cpp
    )

add_executable(VastTakeHome ${TARGET_H} ${TARGET_SRC})





# For testing
enable_testing()

SET(TEST_H
    ${TARGET_H}
    )

SET(TEST_SRC
    ${TARGET_SRC}
    test/test_test.cpp
    test/test_simulation.cpp
    )

add_executable(test_sim ${TEST_H} ${TEST_SRC})

# target_include_directories(test_sim ${CMAKE_CURRENT_SOURCE_DIR}/test)

target_link_libraries(
    test_sim
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_sim)