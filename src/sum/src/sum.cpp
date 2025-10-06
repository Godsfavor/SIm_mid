#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <iostream>

// Global variable to store the sum
double sum = 0.0;

void topic_callback(const std_msgs::msg::Float64::SharedPtr msg)
{
    // Add the received number to the sum
    sum += msg->data;
    
    // Display the current sum
    std::cout << "Received: " << msg->data << " | Total sum: " << sum << std::endl;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("subscriber");
    auto subscription = node->create_subscription<std_msgs::msg::Float64>(
        "topic", 10, topic_callback);
    
    std::cout << "Sum node started. Initial sum: " << sum << std::endl;
    
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}