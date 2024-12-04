cmake_minimum_required(VERSION 2.8.3)
project(traffic_light)
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs cv_bridge sensor_msgs image_transport message_generation )
find_package( OpenCV REQUIRED )

#Res_Color - msgs
 add_message_files(
   FILES
   Res_Color.msg
#   Message2.msg
 )

generate_messages(DEPENDENCIES std_msgs)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES process_video
  CATKIN_DEPENDS roscpp std_msgs cv_bridge sensor_msgs image_transport message_generation
)
include_directories( ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})



#traffic_light
add_executable(check_color src/check_color.cpp)
add_dependencies(check_color ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(check_color ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )


