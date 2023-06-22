#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl_ros/point_cloud.h>

class CostmapGenerator {
public:
    CostmapGenerator() : voxel_leaf_size_(0.1) {
        ros::NodeHandle nh("~");
        sub_pointcloud_ = nh.subscribe("voxel_cloud", 1, &CostmapGenerator::pointcloudCallback, this);
        pub_costmap_ = nh.advertise<sensor_msgs::PointCloud2>("costmap", 1);
    }

    void pointcloudCallback(const sensor_msgs::PointCloud2ConstPtr& pointcloud_msg) {
        // Convert PointCloud2 message to PCL point cloud
        pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_pointcloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromROSMsg(*pointcloud_msg, *pcl_pointcloud);

        // Perform voxel downsampling
        pcl::PointCloud<pcl::PointXYZ>::Ptr downsampled_pointcloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
        voxel_grid.setInputCloud(pcl_pointcloud);
        voxel_grid.setLeafSize(voxel_leaf_size_, voxel_leaf_size_, voxel_leaf_size_);
        voxel_grid.filter(*downsampled_pointcloud);

        // Generate costmap
        pcl::PointCloud<pcl::PointXYZ>::Ptr costmap(new pcl::PointCloud<pcl::PointXYZ>);
        generateCostmap(downsampled_pointcloud, costmap);

        // Convert costmap to PointCloud2 message and publish
        sensor_msgs::PointCloud2 costmap_msg;
        pcl::toROSMsg(*costmap, costmap_msg);
        pub_costmap_.publish(costmap_msg);
    }






//

void generateCostmap(const pcl::PointCloud<pcl::PointXYZ>::Ptr& input_cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr& output_cloud) {
    // Calculate cost based on whether a voxel is covered by the point cloud
    // Add your cost calculation logic here, you can modify the example code below as per your requirements

    // Create the output point cloud with the same size as the input point cloud
    output_cloud->width = input_cloud->width;
    output_cloud->height = input_cloud->height;
    output_cloud->points.resize(input_cloud->points.size());

    // Iterate through each point in the input point cloud
    for (size_t i = 0; i < input_cloud->points.size(); ++i) {
        // Calculate the cost based on whether the voxel is covered by the point cloud
        // Modify this logic based on your specific needs
        float cost = 0.0;  // Default cost value

        // Check if the voxel is covered by the point cloud
        if (!std::isnan(input_cloud->points[i].x) && !std::isnan(input_cloud->points[i].y) && !std::isnan(input_cloud->points[i].z)) {
            cost = 1.0;  // Set a non-zero cost value if the voxel is covered
        }

        // Assign the cost value to the corresponding voxel in the output point cloud
        output_cloud->points[i].x = input_cloud->points[i].x;
        output_cloud->points[i].y = input_cloud->points[i].y;
        output_cloud->points[i].z = cost;  // Assign the cost value to the 'z' field
    }
    }










private:
    ros::Subscriber sub_pointcloud_;
    ros::Publisher pub_costmap_;
    double voxel_leaf_size_;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "costmap_generator");
    CostmapGenerator costmap_generator;
    ros::spin();
    return 0;
}
