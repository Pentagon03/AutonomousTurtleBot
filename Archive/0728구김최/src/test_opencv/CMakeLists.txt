cmake_minimum_required(VERSION 2.8.3)
project(test_opencv)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs cv_bridge sensor_msgs image_transport )

find_package( OpenCV REQUIRED )  

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES test_opencv
  CATKIN_DEPENDS roscpp std_msgs cv_bridge sensor_msgs image_transport
)

include_directories( ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_executable(opencv_test1 src/opencv_test1.cpp)
add_dependencies(opencv_test1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(opencv_test1 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(ex1 src/ex1.cpp)
add_dependencies(ex1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ex1 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(std1 src/std1.cpp)
add_dependencies(std1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(std1 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(ex2 src/ex2.cpp)
add_dependencies(ex2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ex2 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(ex3 src/ex3.cpp)
add_dependencies(ex3 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ex3 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )
