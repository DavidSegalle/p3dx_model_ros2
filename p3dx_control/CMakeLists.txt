cmake_minimum_required(VERSION 3.5)
project(p3dx_control)
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(controller_manager REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(mover mover.cpp)

ament_target_dependencies(mover
  rclcpp
  std_msgs
  controller_manager
  geometry_msgs)

install(TARGETS mover
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/
  DESTINATION include)


ament_export_include_directories(include)
ament_export_dependencies(std_msgs)

#target_include_directories(target PUBLIC include ${Boost_INCLUDE_DIRS})

ament_package()


