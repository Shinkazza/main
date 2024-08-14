#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <unistd.h>
#include <termios.h>


// Function to get keyboard input without blocking
char getch()
{
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
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "lift_pub");
    ros::NodeHandle n;
    ros::Publisher lift_pub = n.advertise<std_msgs::Int32>("lift", 1000);

    ros::Rate loop_rate(100);

    int lift_state;
    std_msgs::Int32 lift_msg;
	lift_msg.data = lift_state;
    lift_pub.publish(lift_msg);
    ROS_INFO("Published lift: %d", lift_msg.data);

    while (ros::ok())
    {

        char c = getch();
        if (c == '8')
        {
            lift_state = -1;
        }
        else if (c == '9')
        {
            lift_state = 0;
        }
        else if (c == '0')
        {
            lift_state = 1;
        }


        lift_msg.data = lift_state;
        lift_pub.publish(lift_msg);
        ROS_INFO("Published lift: %d", lift_msg.data);

        loop_rate.sleep();
    }


    return 0;
}




