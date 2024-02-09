cmake_minimum_required(VERSION 3.5)

project(p3dx_gazebo)
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(ament_cmake REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(p3dx_control REQUIRED)
find_package(p3dx_description REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
#install(DIRECTORY include/
#  DESTINATION include)
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})


ament_export_include_directories(include)
ament_export_dependencies(std_msgs)

#target_include_directories(target PUBLIC include ${Boost_INCLUDE_DIRS})

ament_package()
