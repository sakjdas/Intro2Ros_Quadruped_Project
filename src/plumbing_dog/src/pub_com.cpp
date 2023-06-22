#include <ros/ros.h>
#include <mav_msgs/Actuators.h>

// 话题：/commands
// 消息: mav_msgs/Actuators

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "my_controll");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<mav_msgs::Actuators>("/commands", 10);
    ros::Rate rate(0.1); // HZ
    mav_msgs ::Actuators actuator;
    std::vector<double> velocity_forward;
    std::vector<double> velocity_right;
    std::vector<double> velocity_left;

    velocity_forward = {0.0, 90.0, 0.0, 0.0, 7.0};
    velocity_right = {0.0, 45.0, 0.0, 0.0, 7.0};
    velocity_left = {0.0, 135.0, 0.0, 0.0, 7.0};

    // Time
    //

    bool flag = true;

    while (ros::ok())
    {
        if (flag)
        {

            actuator.angular_velocities = velocity_forward;

            ros::Time right_now = ros::Time::now();
            ROS_INFO("start time right %.2f", right_now.toSec());
            // forward function sleeps 5 seconds e.g moving right/left 
            ros::Duration pause(5);
            pause.sleep();
            ROS_INFO("end time right %.2f", right_now.toSec());

            flag = false;
        }
        else
        {

            ros::Time right_now = ros::Time::now();
            ROS_INFO("start time forward %.2f", right_now.toSec());
            // sleep 15s
            ros::Duration pause2(15);
            pause2.sleep();
            ROS_INFO("end time forward %.2f", right_now.toSec());

            actuator.angular_velocities = velocity_right;
            flag = true;
        }

        pub.publish(actuator);

        ros::spinOnce();

        rate.sleep();
    }
    return 0;
}
