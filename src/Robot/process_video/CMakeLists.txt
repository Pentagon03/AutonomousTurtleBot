cmake_minimum_required(VERSION 2.8.3)
project(process_video)

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
add_executable(pub_video src/pub_video.cpp)
add_dependencies(pub_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(pub_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#add_executable(sub_video src/sub_video.cpp)
#add_dependencies(sub_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(sub_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#add_executable(save_video src/save_video.cpp)
#add_dependencies(save_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(save_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#add_executable(change_video_hsv src/change_video_hsv.cpp)
#add_dependencies(change_video_hsv ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(change_video_hsv ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#add_executable(send_video src/send_video.cpp)
#add_dependencies(send_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(send_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#which_way


#traffic_light
add_executable(sub_video src/sub_video.cpp)
add_dependencies(sub_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(sub_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )




