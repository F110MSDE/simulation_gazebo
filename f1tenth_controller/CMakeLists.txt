cmake_minimum_required(VERSION 2.8.3)
project(f1tenth_controller)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)



## Generate messages in the 'msg' folder
add_message_files(
  FILES
  racecar.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(sim_connector src/sim_connector.cpp)
target_link_libraries(sim_connector ${catkin_LIBRARIES})
add_dependencies(sim_connector ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(key_controller src/key_controller.cpp)
target_link_libraries(key_controller ${catkin_LIBRARIES})
add_dependencies(key_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(converter src/converter.cpp)
target_link_libraries(converter ${catkin_LIBRARIES})
add_dependencies(converter ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(converter_uint64 src/converter_uint64.cpp)
target_link_libraries(converter_uint64 ${catkin_LIBRARIES})
add_dependencies(converter_uint64 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(converter2 src/converter2.cpp)
target_link_libraries(converter2 ${catkin_LIBRARIES})
add_dependencies(converter2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
