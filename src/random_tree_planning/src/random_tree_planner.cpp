#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Point.h>
#include <random>

// 全局变量
nav_msgs::OccupancyGrid occupancy_grid;

nav_msgs::Path generateRandomPath()
{
    nav_msgs::Path path;
    path.header.frame_id = "world";

    // 生成随机路径点
    for (int i = 0; i < 10; ++i)
    {
        geometry_msgs::PoseStamped pose;
        pose.pose.position.x = rand() % occupancy_grid.info.width;
        pose.pose.position.y = rand() % occupancy_grid.info.height;
        pose.pose.orientation.w = 1.0;
        path.poses.push_back(pose);
    }

    return path;
}

void occupancyGridCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
    occupancy_grid = *msg;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "random_tree_planner_node");
    ros::NodeHandle nh;

    // 创建订阅器和发布器
    ros::Subscriber occupancy_grid_sub = nh.subscribe("occupancy_grid", 1, occupancyGridCallback);
    ros::Publisher path_pub = nh.advertise<nav_msgs::Path>("/path", 10);

    // 发布频率控制
    ros::Rate rate(1); // 1Hz

    while (ros::ok())
    {
        // 检查是否收到有效的Occupancy Grid地图
        if (!occupancy_grid.data.empty())
        {
            // 生成随机路径
            nav_msgs::Path random_path = generateRandomPath();

            // 发布路径消息
            path_pub.publish(random_path);
        }

        // 按照发布频率休眠
        rate.sleep();

        // 处理回调函数
        ros::spinOnce();
    }

    return 0;
}
