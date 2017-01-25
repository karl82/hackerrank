cmake_minimum_required(VERSION 3.6)
project(hackerrank CXX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

add_subdirectory(dijkstrashortreach)
add_subdirectory(fraudulent-activity-notifications)
add_subdirectory(projecteuler/challenges)
