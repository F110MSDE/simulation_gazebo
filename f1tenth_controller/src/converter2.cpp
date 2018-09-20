#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/Float64.h"
#include "f1tenth_controller/racecar.h"

#define PI 3.141592

class Converter
{
private:
    ros::NodeHandle nh_c;
    ros::Subscriber sub_angle;
    ros::Subscriber sub_speed;
    ros::Publisher pub;
    f1tenth_controller::racecar msg_pub;
    double angle_temp;
    double speed_temp;
    double angle;
    double velocity;
public:
    Converter(const ros::NodeHandle h)
    : nh_c(h)
    {
        sub_angle = nh_c.subscribe("/desired_angle_val", 1, &Converter::angleCallback, this);
        sub_speed = nh_c.subscribe("/desired_speed_val", 1, &Converter::speedCallback, this);
        pub = nh_c.advertise<f1tenth_controller::racecar>("/racecar_param", 1);
        angle_temp = 99;
        speed_temp = 4;
        ROS_INFO("start converter node");
        ROS_INFO("run your nodes for auto drive");
    }
    void angleCallback(const std_msgs::Float64::ConstPtr& msg_sub);
    void speedCallback(const std_msgs::Float64::ConstPtr& msg_sub);
    void pubCallback();
    void convert_value();
};

void Converter::angleCallback(const std_msgs::Float64::ConstPtr& msg_sub)
{
    this->angle_temp = msg_sub->data;
}

void Converter::speedCallback(const std_msgs::Float64::ConstPtr& msg_sub)
{
    this->speed_temp = msg_sub->data;
}

void Converter::pubCallback()
{
    msg_pub.velocity = this->velocity;
    msg_pub.angle = this->angle;
    this->pub.publish(msg_pub);
}

void Converter::convert_value()
{

    switch((int)this->speed_temp)
    {
    case 3:
    case 4:
        this->velocity = 0;
        break;
    case 5:
        this->velocity = 34;
        break;
    case 6:
        this->velocity = 38;
        break;
    case 7:
        this->velocity = 60;
        break;   
    }

    this->angle = (-1)*((this->angle_temp-99))*(PI/180.0);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "converter");
    ros::NodeHandle nh;

    Converter obj(nh);
    ros::Rate rate(50);
    
    while(ros::ok())
    {
        ros::spinOnce();
        obj.convert_value();
        obj.pubCallback();
        rate.sleep();
    }

    return 0;
}
