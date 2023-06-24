#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <iostream>
using namespace std;

// Declaration of a ROS publisher variable named pub_point_cloud2
ros::Publisher pub_point_cloud2;
 
bool is_K_empty = 1;
double K[9];
//     [fx  0 cx]
// K = [ 0 fy cy]
//     [ 0  0  1]

// This function is called whenever a new depth image is received.
void img_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
    // Step1: 读取深度图
    //ROS_INFO("image format: %s %dx%d", img_msg->encoding.c_str(), img_msg->height, img_msg->width);
    int height = img_msg->height;
    int width = img_msg->width;
    // 通过指针强制转换，读取为16UC1数据，单位是mm
    unsigned short *depth_data = (unsigned short*)&img_msg->data[0];
    
    // Step2: 深度图转点云
    sensor_msgs::PointCloud2 point_cloud2;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    // The nested loops iterate over each pixel of the depth image.
    // It calculates the x, y, and z coordinates of the point using the depth value and camera intrinsics.
    for(int uy=0; uy<height; uy++)
    {
        for(int ux=0; ux<width; ux++)
        {
            float x, y, z;
            // uint8_t zi = *(depth_data + (uy*width + ux) * 2 ); //mm
            // uint8_t zi_plus_1 = *(depth_data + (uy*width + ux) * 2 + 1); //mm
            // uint16_t int_millimeters = (zi_plus_1 << 8) | zi; //combine
            // z = int_millimeters / 1000; //m
            z = *(depth_data + uy*width + ux) / 1000.0;
            float fx = K[0];
            float fy = K[4];
            float ux0 = K[2];
            float uy0 = K[5];
            // see wehether depth is 0 or not
            // If the depth value is not zero, it creates a pcl::PointXYZ point and adds it to the cloud point cloud.
            if(z!=0)
            {
                x = z * (ux - ux0) / fx;
                y = z * (uy - uy0) / fy;
                pcl::PointXYZ p(x, y, z);
                cloud->push_back(p);
                
            }
        }
    }
    // Conversion of the pcl::PointCloud<pcl::PointXYZ> to sensor_msgs::PointCloud2 using pcl::toROSMsg function
    pcl::toROSMsg(*cloud, point_cloud2);
    point_cloud2.header.frame_id = "depth_camera";
    pub_point_cloud2.publish(point_cloud2);
}
 
 
void camera_info_callback(const sensor_msgs::CameraInfoConstPtr &camera_info_msg)
{
    // 读取相机参数
    if(is_K_empty)
    {
        for(int i=0; i<9; i++)
        {
            K[i] = camera_info_msg->K[i];
        }
        is_K_empty = 0;
    }
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_cloud");
    ros::NodeHandle n;
    ros::Subscriber sub_cmara_info = n.subscribe("/unity_ros/RoboDog/base_link/SensorHolder/Sensors/DepthCamera/camera_info", 1, camera_info_callback);
    ros::Subscriber sub_img = n.subscribe("/unity_ros/RoboDog/base_link/SensorHolder/Sensors/DepthCamera/image_raw", 100, img_callback);
    pub_point_cloud2 = n.advertise<sensor_msgs::PointCloud2>("/unity_ros/RoboDog/base_link/SensorHolder/Sensors/DepthCamera/point_cloud", 1000);
    
    ROS_INFO("Runing ...");
    ros::spin();
    return 0;
}