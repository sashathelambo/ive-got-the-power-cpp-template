cmake_minimum_required(VERSION 3.24)

project(ive-got-the-power)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

# Driver program that emits CSV timings
add_executable(main
  main.cpp
  src/power.cpp
)

# Tests
add_executable(power_test tests/power_test.cpp src/power.cpp)
target_link_libraries(power_test PRIVATE Catch2::Catch2WithMain)
