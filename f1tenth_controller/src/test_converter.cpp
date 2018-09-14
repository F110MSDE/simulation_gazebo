#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "f1tenth_controller/racecar.h"

#define PI 3.141592

class Converter
{
private:
    ros::NodeHandle nh_c;
    ros::Subscriber sub;
    ros::Publisher pub;
    f1tenth_controller::racecar msg_pub;
    int servo_data;
    int temp_velocity;
    int temp_angle;
    double angle;
    double velocity;
public:
    Converter(const ros::NodeHandle h)
    : nh_c(h)
    {
        sub = nh_c.subscribe("/servo", 1, &Converter::subCallback, this);
        pub = nh_c.advertise<f1tenth_controller::racecar>("/racecar_param", 1);
        ROS_INFO("start converter node");
        ROS_INFO("run your nodes for auto drive");
    }
    void subCallback(const std_msgs::UInt16::ConstPtr& msg_sub);
    void pubCallback();
    void convert_value();
};

void Converter::subCallback(const std_msgs::UInt16::ConstPtr& msg_sub)
{
    this->servo_data = msg_sub->data;
    this->convert_value();
    this->pubCallback();
}

void Converter::pubCallback()
{
    this->pub.publish(msg_pub);
}

void Converter::convert_value()
{
    this->temp_velocity = this->servo_data/1000;
    this->temp_angle = this->servo_data%1000;

    switch(this->temp_velocity)
    {
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

    this->angle = (-1)*((double)(this->temp_angle-99))*(PI/180.0);

    msg_pub.velocity = this->velocity;
    msg_pub.angle = this->angle;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "converter");
    ros::NodeHandle nh;

    Converter obj(nh);
    ros::spin();

    return 0;
}
