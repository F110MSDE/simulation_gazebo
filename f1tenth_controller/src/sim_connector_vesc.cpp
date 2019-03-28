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
    ros::Subscriber sub_s;
    ros::Subscriber sub_a;
    
    std_msgs::Float64 velocity;
    std_msgs::Float64 angle;

    double temp_s;
    double temp_a;

public:
    Connector(const ros::NodeHandle &h)
    : nh_cn(h)
    {
        sub_s = nh_cn.subscribe("/racecar_speed", 1, &Connector::subCallback_s, this);
        sub_a = nh_cn.subscribe("/racecar_angle", 1, &Connector::subCallback_a, this);

        left_front_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/left_front_wheel_velocity_controller/command", 1);
        right_front_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/right_front_wheel_velocity_controller/command", 1);
        left_rear_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/left_rear_wheel_velocity_controller/command", 1);
        right_rear_wheel_velocity_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/right_rear_wheel_velocity_controller/command", 1);
        
        left_steering_hinghe_position_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/left_steering_hinge_position_controller/command", 1);
        right_steering_hinghe_position_pub = nh_cn.advertise<std_msgs::Float64>("/racecar/right_steering_hinge_position_controller/command", 1);
        
        ROS_INFO("start connector node");
    }
    void subCallback_s(const std_msgs::Float64::ConstPtr& msg_sub);
    void subCallback_a(const std_msgs::Float64::ConstPtr& msg_sub);
    void pubCallback_s();
    void pubCallback_a();
};

void Connector::subCallback_s(const std_msgs::Float64::ConstPtr& msg_sub)
{
    this->temp_s = (double)msg_sub->data;
    this->velocity.data = this->temp_s;
    this->pubCallback_s();
}

void Connector::subCallback_a(const std_msgs::Float64::ConstPtr& msg_sub)
{
    this->temp_a = (double)msg_sub->data;
    this->angle.data = this->temp_a;
    this->pubCallback_a();
}

void Connector::pubCallback_s()
{
    this->left_front_wheel_velocity_pub.publish(velocity);
    this->right_front_wheel_velocity_pub.publish(velocity);
    this->left_rear_wheel_velocity_pub.publish(velocity);
    this->right_rear_wheel_velocity_pub.publish(velocity);
    ROS_INFO("send speed   : %f", temp_s);
    std::cout<<std::endl;
}

void Connector::pubCallback_a()
{
    this->left_steering_hinghe_position_pub.publish(angle);
    this->right_steering_hinghe_position_pub.publish(angle);
    ROS_INFO("send angle   : %f", temp_a);
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