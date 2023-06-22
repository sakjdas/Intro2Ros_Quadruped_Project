#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

ros::Publisher pub_voxel_cloud;

void pointCloudCallback(const sensor_msgs::PointCloud2::ConstPtr& cloud_msg)
{
    // 将ROS消息转换为PCL点云对象
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*cloud_msg, *cloud);

    // 创建体素滤波器对象
    pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
    voxel_filter.setInputCloud(cloud);
    voxel_filter.setLeafSize(0.05, 0.05, 0.05); // 设置体素大小

    // 执行体素滤波
    pcl::PointCloud<pcl::PointXYZ>::Ptr voxel_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    voxel_filter.filter(*voxel_cloud);

    // 将PCL点云对象转换为ROS消息
    sensor_msgs::PointCloud2 voxel_cloud_msg;
    pcl::toROSMsg(*voxel_cloud, voxel_cloud_msg);
    voxel_cloud_msg.header = cloud_msg->header;

    // 发布体素点云消息
    pub_voxel_cloud.publish(voxel_cloud_msg);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "voxel_grid_filter");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2>("point_cloud", 1000, pointCloudCallback);
    pub_voxel_cloud = nh.advertise<sensor_msgs::PointCloud2>("voxel_cloud", 1000);

    ros::spin();

    return 0;
}
