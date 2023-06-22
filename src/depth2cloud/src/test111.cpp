#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>


//#include <cv_bridge/cv_bridge.h>


#include <iostream>
using namespace std;
 
ros::Publisher pub_point_cloud2;
 
// from /unity_ros/RoboDog/base_link/SensorHolder/Sensors/DepthCamera/camera_info
// intrisic matrix
double K[9] = {120.0, 0.0, 160.0, 0.0, 120.0, 120.0, 0.0, 0.0, 1.0};

//     [fx  0 cx]
// K = [ 0 fy cy]
//     [ 0  0  1]

void img_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
    // Step1: 读取深度图
    //ROS_INFO("image format: %s %dx%d", img_msg->encoding.c_str(), img_msg->height, img_msg->width);
    int height = img_msg->height;//240
    int width = img_msg->width;//320
    // 通过指针强制转换，读取为16UC1数据，单位是mm
    unsigned short *depth_data = (unsigned short*)&img_msg->data[0];
    
    // Step2: 深度图转点云
    sensor_msgs::PointCloud2 point_cloud2;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    for(int uy=0; uy<height; uy++)
    {
        for(int ux=0; ux<width; ux++)
        {
            float x, y, z;
            z = *(depth_data + uy*width + ux) / 1000.0;
            if(z!=0)
            {
                x = z * (ux - K[2]) / K[0];
                y = z * (uy - K[5]) / K[4];
                pcl::PointXYZ p(z, x, -y);
                cloud->push_back(p);
                
            }
        }
    }
    // Step3: 发布点云
    pcl::toROSMsg(*cloud, point_cloud2);
    point_cloud2.header.frame_id = "world";
    pub_point_cloud2.publish(point_cloud2);
}
 

 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_cloud");
    ros::NodeHandle n;
    // 订阅D435i的深度图，在其回调函数中把深度图转化为点云，并发布出来
    ros::Subscriber sub_img = n.subscribe("/unity_ros/RoboDog/base_link/SensorHolder/Sensors/DepthCamera/image_raw", 100, img_callback);


    pub_point_cloud2 = n.advertise<sensor_msgs::PointCloud2>("point_cloud", 1000);
    ROS_INFO("Runing ...");
    ros::spin();
    return 0;
}
