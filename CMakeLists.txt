cmake_minimum_required(VERSION 2.8)
project(CLUSTERSIM C)

# Adding path under project folder where I put custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/share/cmake-2.8/Modules/Find*.cmake for more examples
find_package(LibConfig REQUIRED)
find_package(PNG       REQUIRED)
find_package(Lua52     REQUIRED)

find_package(Check     REQUIRED)
find_package(Threads   REQUIRED)
find_package(RT        REQUIRED)


set(CMAKE_C_FLAGS "-Wall -std=c11")

add_subdirectory(src)






