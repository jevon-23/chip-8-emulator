# skeleton from : https://github.com/ttroy50/cmake-examples/blob/master/01-basic/B-hello-headers/CMakeLists.txt
# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.2)

# Set the project name
project (chip8)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/build/main.c src/utils/utils.c src/cpu/cpu.c src/memory/mem.c src/instructions/instructions.c src/stack/stack.c src/display/display.c src/timers/timer.c src/keypad/keypad.c
    )

# Add an executable with the above sources
add_executable(chip8 ${SOURCES} )

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(chip8
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    )
# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
# testing memory
add_executable(testMem src/memory/test/test.cpp src/memory/mem.c src/utils/utils.c)
target_include_directories(testMem
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inlcude
    )
add_test(testAll testMem)

target_link_libraries(
    testMem
    gtest_main
    )

# testing display
add_executable(testDisplay src/display/test/test.cpp src/display/display.c)
target_include_directories(testDisplay
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    )
add_test(testAll testDisplay)

target_link_libraries(
    testDisplay
    gtest_main
    )

# testing timers
add_executable(testTimers src/timers/test/test.cpp src/timers/timer.c)
target_include_directories(testTimers
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inlcude
    )
add_test(testAll testTimers)

target_link_libraries(
    testTimers
    gtest_main
    )

# testing keypad
add_executable(testKeypad src/keypad/test/test.cpp src/keypad/keypad.c)
target_include_directories(testKeypad
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inlcude
    )
add_test(testAll testKeypad)

target_link_libraries(
    testKeypad
    gtest_main
    )

# testing stack
add_executable(testStack src/stack/test/test.cpp src/stack/stack.c)
target_include_directories(testStack
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inlcude
    )
add_test(testAll testStack)

target_link_libraries(
    testStack
    gtest_main
    )


# testing instructions
add_executable(testInstruct src/instructions/test/test.cpp src/instructions/instructions.c)
target_include_directories(testInstruct
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inlcude
    )
add_test(testAll testInstruct)

target_link_libraries(
    testInstruct
    gtest_main
    )

# testing utils
add_executable(testUtils src/utils/test/test.cpp src/utils/utils.c)
target_include_directories(testUtils
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inlcude
    )
add_test(testAll testUtils)

target_link_libraries(
    testUtils
    gtest_main
    )

# testing cpu
add_executable(testCpu src/cpu/test/test.cpp src/cpu/cpu.c src/display/display.c src/memory/mem.c src/instructions/instructions.c src/stack/stack.c src/timers/timer.c src/keypad/keypad.c)
target_include_directories(testCpu
    PRIVATE
    ${PROJECT_SOURCE_DIR}/inlcude
    )
add_test(testAll testCpu)

target_link_libraries(
    testCpu
    gtest_main
    )
