project(Test)

cmake_minimum_required(VERSION 3.12)

file (GLOB SOURCES "../../include/*.h" "../../src/*.cpp" "./*.cpp")

add_executable(test ${SOURCES})

set (CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++ -Werror -g -std=c++11 -fprofile-arcs -ftest-coverage")

target_include_directories(test PRIVATE "../../include")

file (GLOB DEPS "../../deps/*")

foreach(subdir ${DEPS})
    file (GLOB dep_sources "${subdir}/include/*.cpp" "${subdir}/src/*.cpp")
    target_sources(test PRIVATE "${dep_sources}")
    target_include_directories(test PRIVATE "${subdir}/include")
endforeach()
