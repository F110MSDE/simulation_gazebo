#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "f1tenth_controller/racecar.h"


class Connector
{
private:
    ros::NodeHandle nh_cn;
    ros::Publisher left_front_wheel_velocity_pub;
    ros::Publisher right_front_wheel_velocity_pub;
    ros::Publisher left_rear_wheel_velocity_pub;
    ros::Publisher right_rear_wheel_velocity_pub;
    ros::Publisher left_steering_hinghe_position_pub;
    ros::Publisher right_steering_hinghe_position_pub;
    ros::Subscriber racecar_sub;
    std_msgs::Float64 velocity;
    std_msgs::Float64 angle;
public:
    Connector(const ros::NodeHandle &h)
    : nh_cn(h)
    {
        racecar_sub = nh_cn.subscribe("/racecar_param", 1, &Connector::subCallback, this);
        left_front_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/left_front_wheel_velocity_controller/command", 1);
        right_front_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/right_front_wheel_velocity_controller/command", 1);
        left_rear_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/left_rear_wheel_velocity_controller/command", 1);
        right_rear_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/right_rear_wheel_velocity_controller/command", 1);
        left_steering_hinghe_position_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/left_steering_hinge_position_controller/command", 1);
        right_steering_hinghe_position_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/right_steering_hinge_position_controller/command", 1);
        ROS_INFO("start connector node");
    }
    void subCallback(const f1tenth_controller::racecar::ConstPtr& msg);
    void pubCallback();
};

void Connector::subCallback(const f1tenth_controller::racecar::ConstPtr& msg)
{
    double temp_v, temp_a;
    temp_v = (double)msg->velocity;
    temp_a = (double)msg->angle;
    this->velocity.data = temp_v;
    this->angle.data = temp_a;
    this->pubCallback();
}

void Connector::pubCallback()
{
    this->left_steering_hinghe_position_pub.publish(angle);
    this->right_steering_hinghe_position_pub.publish(angle);
    this->left_front_wheel_velocity_pub.publish(velocity);
    this->right_front_wheel_velocity_pub.publish(velocity);
    this->left_rear_wheel_velocity_pub.publish(velocity);
    this->right_rear_wheel_velocity_pub.publish(velocity);
    double temp_v, temp_a;
    temp_v = this->velocity.data;
    temp_a = this->angle.data;
    ROS_INFO("send velocity : %f", temp_v);
    ROS_INFO("send angle    : %f", temp_a);
    std::cout<<std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sim_connector");
    ros::NodeHandle nh;

    Connector obj(nh);
    ros::spin();

    return 0;
}