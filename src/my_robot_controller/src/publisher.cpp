#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("publisher");
    auto publisher = node->create_publisher<std_msgs::msg::String>("topic", 10);
    
    std_msgs::msg::String message;
    auto publish_count = 0;
    rclcpp::WallRate loop_rate(500ms);
    
    RCLCPP_INFO(node->get_logger(), "Publisher node started!");
    
    while (rclcpp::ok()){
        message.data = "Hello, world! " + std::to_string(publish_count++);
        RCLCPP_INFO(node->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher->publish(message);
        loop_rate.sleep();
    }
    
    rclcpp::shutdown();
    return 0;
}
