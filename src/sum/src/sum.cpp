#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <iostream>

void topic_callback(const std_msgs::msg::Float64::SharedPtr msg)
{
    std::cout << "Received number: " << msg->data << std::endl;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("subscriber");
    auto subscription = node->create_subscription<std_msgs::msg::Float64>(
        "topic", 10, topic_callback);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}