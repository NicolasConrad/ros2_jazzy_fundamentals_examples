/*
 * Demonstrates publishing messages on a ROS 2 topic
 */
#include "rclcpp/rclcpp.hpp" // ROS 2 C++ client library
#include "std_msgs/msg/string.hpp" // standard message type for strings

using namespace std::chrono_literals; // handles time (since we are publishing at a specified frequency)

class MinimalCppPublisher : public rclcpp::Node // extending the Node class located in the rclcpp::Node library
{
    public:
        MinimalCppPublisher() : Node("minimal_cpp_publisher"), count_(0)
        {
            publisher_ = create_publisher<std_msgs::msg::String>(
                "/cpp_example_topic", 10
            );

            timer_ = create_wall_timer(500ms, 
                std::bind(&MinimalCppPublisher::timerCallback, this)
            );

            RCLCPP_INFO(get_logger(), "Publishing at 2Hz");
        }

        void timerCallback()
        {
            auto message = std_msgs::msg::String();
            message.data = "Hello World! " + std::to_string(count_++);
            publisher_ -> publish(message);
        }

    private:
        size_t count_; // keeps track of the number of messages published
        rclcpp::TimerBase::SharedPtr timer_; // Timer
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

#ifndef TEST_EXCLUDE_MAIN
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv); // initialize ROS 2

    auto minimal_cpp_publisher_node = std::make_shared<MinimalCppPublisher>(); // Instantiate our MinimalCppPublisher node
    rclcpp::spin(minimal_cpp_publisher_node); // spin the node so that the callback gets called at the desired frequency.

    rclcpp::shutdown(); // when done (i.e. press ctrl+c), the node is closed and ROS 2 will shut down.

    return 0;
}
#endif