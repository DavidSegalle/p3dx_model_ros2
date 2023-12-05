#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("mover");

  //ros::Publisher twist_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  //geometry_msgs::msg::Twist
  auto twist_pub = node->create_publisher<geometry_msgs::msg::Twist>("cmd_vel",
  1000);

  geometry_msgs::msg::Twist t;
  char cmd[50];
  rclcpp::Rate loop_rate(10);
  t = geometry_msgs::msg::Twist();

  while (rclcpp::ok())
  {
    std::cin.getline(cmd, 50);

    switch (cmd[0]) {
    case 'w':
      t.linear.x += 0.1;
      break;
    case 's':
      t.linear.x -= 0.1;
      break;
    case 'a':
      t.angular.z += 0.1;
      break;
    case 'd':
      t.angular.z -= 0.1;
      break;
    default:
      t = geometry_msgs::msg::Twist();
      break;
    }

    twist_pub->publish(t);

    rclcpp::spin_some(node);
    loop_rate.sleep();
  }

  return 0;
}
