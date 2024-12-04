cmake_minimum_required(VERSION 2.8.3)
project(fin)
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs cv_bridge sensor_msgs image_transport message_generation )

find_package( OpenCV REQUIRED )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES process_video
  CATKIN_DEPENDS roscpp std_msgs cv_bridge sensor_msgs image_transport message_generation
)

include_directories( ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

#process_video
#add_executable(pub_video src/pub_video.cpp)
#add_dependencies(pub_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(pub_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#add_executable(sub_video src/sub_video.cpp)
#add_dependencies(sub_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(sub_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(fastmove src/fastmove.cpp)
add_dependencies(fastmove ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(fastmove ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(cross src/cross.cpp)
add_dependencies(cross ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(cross ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(light src/light.cpp)
add_dependencies(light ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(light ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#which_way


#traffic_light
#add_executable(sub_video src/sub_video.cpp)
#add_dependencies(sub_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(sub_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )




