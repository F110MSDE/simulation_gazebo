#include <unistd.h>
#include <termios.h>
#include <iostream>

#include "ros/ros.h"
#include "f1tenth_controller/racecar.h"


char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "key_controller");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<f1tenth_controller::racecar>("/racecar_param", 1);
    ros::Rate loop_rate(50);

    f1tenth_controller::racecar msg;
    msg.velocity = 0;
    msg.angle = 0;

    char ch;

    std::cout<<"  w"<<std::endl;
    std::cout<<"a s d"<<std::endl;
    std::cout<<"f : velocity->0"<<std::endl;
    std::cout<<"x : angle->0"<<std::endl;

    while(ros::ok())
    {
        ch = getch();
        switch(ch)
        {
        case 'w':
            msg.velocity += 1;
            break;
        case 'a':
            msg.angle += 0.1;
            break;
        case 's':
            msg.velocity -= 1;
            break;
        case 'd':
            msg.angle -= 0.1;
            break;
        case 'f':
            msg.velocity = 0;
            break;
        case 'x':
            msg.angle = 0;
            break;
        }
        

        pub.publish(msg);
        loop_rate.sleep();
    }
    return 0;
}
