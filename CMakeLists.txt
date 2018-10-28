cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

# Call cmake with -D TESTS=ON to set this flag to true.
option(TESTS "build tests" OFF)

project(amqpcpp-client CXX C)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")


add_subdirectory(third-party/boost-cmake)


SET(AMQP-CPP_LINUX_TCP ON CACHE BOOL "Build libfoo shared library")
add_subdirectory(third-party/AMQP-CPP)
include_directories(third-party/AMQP-CPP/include)

# Core and main are split. This allows us to link core to main and tests.

# Core library. *.cpp should be added here.
add_library(core
  ./src/core.cpp)

# Main entry point.
add_executable(main
  ./src/main.cpp)

# Link core to main.
set_target_properties(main PROPERTIES LINK_FLAGS "-Wl,--no-as-needed")
target_link_libraries(main
  Boost::boost
  Boost::system
  Boost::thread
  pthread
  dl
  ssl
  amqpcpp  
  )

if(TESTS)

  enable_testing()

  # Process the CMakeLists.txt in third-party/googletest, sets project(gtest) and
  # project(gmock), gives access to ${gtest_SOURCE_DIR} and ${gmock_SOURCE_DIR}.
  add_subdirectory(third-party/googletest)

  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

  # Tests. *-test.cpp should be added here.
  add_executable(tests
    ./test/main-test.cpp
    ./test/function-test.cpp
    ./test/class-test.cpp)

  # Link core, pthread and gtest to tests.
  target_link_libraries(tests
    pthread
    gtest
    gtest_main
    core
    )

endif()
