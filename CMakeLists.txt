cmake_minimum_required(VERSION 3.0)

project(test)

find_package(catkin REQUIRED COMPONENTS
      roscpp
       )

#catkin_package( )

include_directories(
        ${catkin_INCLUDE_DIRS}
 )

add_subdirectory(src)

