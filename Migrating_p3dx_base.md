# Failed attempt at migrating the p3dx gazebo model to ROS 2

### Blindly following the guide

Once I had a [p3dx model](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwix0Yn2-f2EAxU3KrkGHSRpAzsQFnoECBEQAQ&url=https%3A%2F%2Fgithub.com%2Fmario-serna%2Fpioneer_p3dx_model&usg=AOvVaw1KeTnZ1CypgLXl7T1k5pcA&opi=89978449) to upgrade I searched for where to begin. Keep in mind that the p3dx gazebo model is consisted of 3 different packages so each step of the process has to be completed 3 times.

A [official guide](https://docs.ros.org/en/humble/How-To-Guides/Migrating-from-ROS1/Migrating-CPP-Packages.html) does exist, while it is quite confusing nothing better appears to exist. A [second guide](https://docs.ros.org/en/humble/How-To-Guides/Migrating-from-ROS1/Migrating-Launch-Files.html) has the steps on how to migrate launch files

### Updating CMakeLists.txt

The beginning is dedicated to changing the build type to use ament_cmake in place of the old catkin_system. This is relatively simple and brought no problems.

Finding updated package names for ros 2 was annoying due to how scattered this information can be, however, after some trying all issues appeared to be solved. 

The rest of the section is referent to changes in function calls and arguments. Changes in the order of function calls can be confusing and the different arguments to be used can cause trouble to someone who _like me_ had very limited knowledge on the workings of this project organization tool.

### Updating the source code

For the entire model there is only one source code file named `control.cpp`, it is very simple in it's nature and therefore _should_ have posed no issue. The only problem I had was that the first line `#include "rclcpp/rclcpp.hpp"` mentioned no such library was available. After some fiddling with export settings and fixing unforseen problems in the `CMakeLists.txt` and `package.xml` files this was solved and no other problems were found.

### Changing the package.xml

Much like the update of CMakeLists it was confusing for someone with no previous experience, however, the hardest step, figuring out new package names was already completed in the `CMakeLists` section.

### Changing the CMake code

First of all, why is this separate from the `CMakeLists` section? everything here is related to that same text file. Every change presented on this section of the guide needs to be interwoven with what was previously done and figuring out the order was a pain in the ass. I mean, seriously, why is this not just one section?

The whole part on including directories and what you should include is kind of confusing, also from this step forward the project is able to compile and source files can be run with the `ros2 run` command. As of this step everything appeared to be working fine, however, next comes the bane of my project.

### Migrating Launch files

When I first looked at this I was confused as to why it was split from the main guide, however, I pressed on.

A couple of attributes changed names for a couple of reasons, ns to namespace being the most significant one (this is foreshadowing).

Params were changed so that no more global parameter exist, this simply means a param tag must **always** be inside a node tag. There is an instance of a global param in the launch files and to this day I do not know what I should have done with in case it was important. Luckily for me, the p3dx model was already a ported model from something which was originally developed for ros melodic. Figuring out that this param was a leftover from that and that it had no actual impact on the program was really annoying and took way longer than expected.

As far as namespaces go the document only makes mention of the change of variable from ns to namespace. While this seems quite simple, some other functionalities no longer work. Pushing a namespace is not doable in ros2 and therefore push_ros_namespace was created as a workaround method. This function caused a plethera of issues, however, the guide has since been updated and makes mention of how to properly use it, problems are unlikely in future attempts of updating packages.

### Random unexpected issues

Getting here took a considerable amount of time and effort. Although the project was already able to compile and launch files were executable, the robot was unable to spawn and some issues were still present.

After some digging I figured that the issues arose from a couple of files where gazebo functions were called. While the inner workings of gazebo have not changed and gazebo is compatible with ros and ros2 some functions have changed. Considering how much time was already sank into the project I decided to ditch the idea of migrating the package and look into `ros_bridge`.

### Using ros_bridge

[Ros_bridge](https://github.com/ros2/ros1_bridge) is a system which allows multiple ros versions to communicate with each other. Getting system requirements issues out of the way: Ros2 versions released for ubuntu 22.04 are not supported by ros_bridge, I was unable to install ros_rolling in ubuntu 20.04 (the issue is likely a small section of a install script and the needed changes are shown in the guide to [build ros humble from source](https://docs.ros.org/en/humble/Installation/Alternatives/Ubuntu-Development-Setup.html) on ubuntu 20.04, however, due to time constraints we did not try anything).

As for possible setups: 

Using ros galactic which has already reached EOL together with ros noetic on ubuntu 20.04 was the most successful solution of the entire project. We could use teleop on ros2 galactic as well as reading all the robots telemetry data while the robot ran on ros noetic. The only problem was that I was unable to launch robots from ros2 into the gazebo simulation.

Using ros rolling with ubuntu 22.04 gave promising results, installing ros noetic was problematic but a solution was found by using mamba to sandbox the system. Ros bridge works on the system, however, the gazebo package had issues and no model was able to launch. Therefore we had communication between both ros version but were left without the model.

Other attempts all fell into major issues on compatibility for ros_bridge or inability to run ros on the necessary systems.

### What I should have done

If i had the knowledge I have now I would just grab the urdf model and check how to load urdf models into gazebo using ros2. There are plenty of guides and tutorials which appear quite simple and make use of python launch files (I don't know why I'm mentioning the python launch file thing, I just found it interesting).

**If you're thinking of converting a random package it shouldn't be the end of the world. If you **
