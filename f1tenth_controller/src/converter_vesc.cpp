#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/UInt16.h"
#include "f1tenth_controller/racecar.h"
#include <math.h>

#define PI 3.141592

class Converter
{
private:
    ros::NodeHandle nh_c;
    ros::Subscriber sub_s;
    ros::Subscriber sub_a;
    ros::Subscriber sub_m;
    ros::Publisher pub;

    double temp_velocity;
    double temp_angle;
    
    f1tenth_controller::racecar msg_p;

    int speed_pub_num;

    int mode;

public:
    Converter(const ros::NodeHandle h)
    : nh_c(h)
    {

        sub_s = nh_c.subscribe("/desired_speed_val", 1, &Converter::subCallback_s, this);
        sub_a = nh_c.subscribe("/desired_angle_val", 1, &Converter::subCallback_a, this);
        sub_m = nh_c.subscribe("/keyboard", 1, &Converter::subCallback_m, this);

        pub = nh_c.advertise<f1tenth_controller::racecar>("/racecar_param", 1);
        
        ROS_INFO("start converter node");
        ROS_INFO("run your nodes for auto drive");

        speed_pub_num = 0;
        mode = 2;
    }

    void subCallback_s(const std_msgs::Float64::ConstPtr& msg_sub);
    void subCallback_a(const std_msgs::Float64::ConstPtr& msg_sub);
    void subCallback_m(const std_msgs::UInt16::ConstPtr& msg_sub);
    void pubCallback();
};


void Converter::subCallback_m(const std_msgs::UInt16::ConstPtr& msg_sub)
{
    this->mode = (int)msg_sub->data/10000;
}


void Converter::subCallback_s(const std_msgs::Float64::ConstPtr& msg_sub)
{
    this->temp_velocity = (double)msg_sub->data;
    speed_pub_num = 0;
    
    if(this->temp_velocity == 0)
    {
        this->temp_velocity = 0;
    }
    else
    {
        this->temp_velocity = (this->temp_velocity/20)*60 + 20;
    }
}

void Converter::subCallback_a(const std_msgs::Float64::ConstPtr& msg_sub)
{
    this->temp_angle = (double)msg_sub->data;
    this->pubCallback();
}

void Converter::pubCallback()
{

    this->msg_p.velocity = this->temp_velocity;
    this->msg_p.angle = (-1)*(this->temp_angle-99)*(PI/180.0);

    if(speed_pub_num < 10) speed_pub_num += 1;
    pub.publish(msg_p);

//    ROS_INFO("mode data = %d", mode);

    if(mode == 2)
    {
        this->temp_velocity = this->temp_velocity*pow(2, -speed_pub_num);
//        ROS_INFO("decrease speed");
    }
}




int main(int argc, char **argv)
{
    ros::init(argc, argv, "converter_vesc");
    ros::NodeHandle nh;

    Converter obj(nh);
    ros::spin();

    return 0;
}
