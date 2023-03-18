add_executable(Demo main.cpp)
target_link_libraries(Demo ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(Tran tran.cpp)
target_link_libraries(Tran ${EIGEN3_LIBRARIES} ${YAML_CPP_LIBRARIES})