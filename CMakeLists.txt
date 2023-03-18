cmake_minimum_required(VERSION 3.0)

project(new_repo)

find_package(PCL REQUIRED)
find_package(yaml-cpp REQUIRED)

find_package(catkin REQUIRED COMPONENTS
      roscpp
       )

#catkin_package( )

include_directories(
        ${catkin_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
        ${YAML_CPP_INCLUDE_DIRS}
 )

add_subdirectory(src)

