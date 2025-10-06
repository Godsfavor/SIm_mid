#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int32.hpp"
#include <iostream>

// Global variable to store the sum
double sum = 0.0;

// Global publisher (we'll initialize it in main)
rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher;

void topic_callback(const std_msgs::msg::Float64::SharedPtr msg)
{
    // Add the received number to the sum
    sum += msg->data;
    
    // Display the current sum
    std::cout << "Received: " << msg->data << " | Total sum: " << sum << std::endl;
    
    // Publish the sum as an integer
    auto message = std_msgs::msg::Int32();
    message.data = static_cast<int>(sum);  // Convert to integer
    publisher->publish(message);
    std::cout << "Published sum: " << message.data << std::endl;
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("subscriber");
    
    // Create the publisher for the "sum" topic
    publisher = node->create_publisher<std_msgs::msg::Int32>("sum", 10);
    
    // Create the subscriber for the input topic
    auto subscription = node->create_subscription<std_msgs::msg::Float64>(
        "topic", 10, topic_callback);
    
    std::cout << "Sum node started. Initial sum: " << sum << std::endl;
    
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}