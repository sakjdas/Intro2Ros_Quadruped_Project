#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

ros::Publisher occupancy_grid_pub;

// 回调函数，当接收到体素格子地图时进行处理
void voxelGridCallback(const sensor_msgs::PointCloud2::ConstPtr& voxel_grid_msg) {
    // 创建OccupancyGrid消息对象
    nav_msgs::OccupancyGrid occupancy_grid;

    // 设置地图的基本信息
    //occupancy_grid.header.frame_id = "map";
    occupancy_grid.header.frame_id = "world";
    occupancy_grid.info.resolution = 0.1;  // 每个格子的分辨率（单位：米）
    occupancy_grid.info.origin.position.x = -5.0;  // 地图左下角的x坐标（单位：米）
    occupancy_grid.info.origin.position.y = -5.0;  // 地图左下角的y坐标（单位：米）
    occupancy_grid.info.origin.orientation.w = 1.0;

    // 将体素格子地图数据转换为PointCloud类型
    pcl::PointCloud<pcl::PointXYZ> voxel_cloud;
    pcl::fromROSMsg(*voxel_grid_msg, voxel_cloud);

    // 计算Occupancy Grid Map的尺寸
    occupancy_grid.info.width = (int)(10.0 / occupancy_grid.info.resolution);  // 地图宽度（单位：格子）
    occupancy_grid.info.height = (int)(10.0 / occupancy_grid.info.resolution);  // 地图高度（单位：格子）

    // 分配存储空间，并初始化地图数据
    occupancy_grid.data.resize(occupancy_grid.info.width * occupancy_grid.info.height, 0);

    // 遍历体素格子地图数据，将其转换为占据格子地图数据
    for (const auto& point : voxel_cloud.points) {
        // 将点的坐标转换为地图上的格子索引
        int x_index = (int)((point.x - occupancy_grid.info.origin.position.x) / occupancy_grid.info.resolution);
        int y_index = (int)((point.y - occupancy_grid.info.origin.position.y) / occupancy_grid.info.resolution);

        // 检查索引是否在合法范围内
        if (x_index >= 0 && x_index < occupancy_grid.info.width && y_index >= 0 && y_index < occupancy_grid.info.height) {
            int index = x_index + y_index * occupancy_grid.info.width;
            occupancy_grid.data[index] = 100;  // 设置为100表示占据
        }
    }

    // 发布占据格子地图消息
    occupancy_grid_pub.publish(occupancy_grid);
}

int main(int argc, char** argv) {
    // 初始化ROS节点
    ros::init(argc, argv, "occupancy_grid_node");
    ros::NodeHandle nh;

    // 创建占据格子地图的发布者
    occupancy_grid_pub = nh.advertise<nav_msgs::OccupancyGrid>("occupancy_grid", 1);

    // 创建体素格子地图的订阅者
    ros::Subscriber voxel_grid_sub = nh.subscribe<sensor_msgs::PointCloud2>("voxel_cloud", 1, voxelGridCallback);
    ROS_INFO("Runing voxel2gridmap");

    ros::spin();

    return 0;
}
