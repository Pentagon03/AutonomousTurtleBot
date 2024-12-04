cmake_minimum_required(VERSION 2.8.3)
project(which_way)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs cv_bridge sensor_msgs image_transport message_generation )

find_package( OpenCV REQUIRED )

find_package( GSL REQUIRED )

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   char_msg.msg
   theta.msg
   Res_Key.msg
#   Message2.msg
 )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES which_way
  CATKIN_DEPENDS roscpp std_msgs cv_bridge sensor_msgs image_transport message_generation
)

include_directories( ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${GSL_INCLUDE_DIRS})



#which_way
#add_executable(calculate_theta src/calculate_theta.cpp)
#add_dependencies(calculate_theta ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(calculate_theta ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#add_executable(check_object src/check_object.cpp)
#add_dependencies(check_object ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(check_object ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

#add_executable(check_road src/check_road.cpp)
#add_dependencies(check_road ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(check_road ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )
add_executable(move_bot src/move_bot.cpp)
add_dependencies(move_bot ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_bot ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(stop_bot src/stop_bot.cpp)
add_dependencies(stop_bot ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(stop_bot ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable(determinant src/determinant.cpp)
add_dependencies(determinant ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(determinant ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${GSL_LIBRARIES})

add_executable(calculate_theta src/calculate_theta.cpp)
add_dependencies(calculate_theta ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(calculate_theta ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${GSL_LIBRARIES})

#subscriber node
#add_executable(input_video src/input_video.cpp)
#add_dependencies(input_video ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(input_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} )
#publisher node
add_executable(PUB src/PUB.cpp)
add_dependencies(PUB ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(PUB ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${GSL_LIBRARIES})

add_executable(OPS src/OPS.cpp)
add_dependencies(OPS ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(OPS ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${GSL_LIBRARIES})





