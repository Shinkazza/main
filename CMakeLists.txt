cmake_minimum_required(VERSION 3.0.2)
project(main)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)


catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(main src/pubsub.cpp src/main.cpp)
add_executable(main_2 src/main_2.cpp)

add_dependencies(main ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(main_2 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(main
   ${catkin_LIBRARIES}
 )

target_link_libraries(main_2
   ${catkin_LIBRARIES}
 )

