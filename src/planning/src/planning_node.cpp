
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_datatypes.h>
#include <tf/LinearMath/Matrix3x3.h>

#define PI M_PI

class planning_node{
    ros::NodeHandle nh;
    ros::Subscriber robot_pos;  //subscribe to current pose
    ros::Subscriber path_sub;   //subscribe to path from move base  
    ros::Subscriber map_sub;    //subscribe to projected_map with steps

    ros::Publisher path_point_pub;  //publish selected path point

    Eigen::Vector2d current_position;
    Eigen::Vector2d current_velocity;
    Eigen::Vector2d current_direction;

    geometry_msgs::Point path_point;
    double hz;  //frequency of the path point publishing
    ros::Timer timer;

    //parameters used to check if there is step in front of robot
    int map_width;
    int map_height;
    double resolution;
    double origin_x;
    double origin_y;
    int occupancy;
    int occupied_count;
    int idx;

public:
    planning_node():hz(50){
        robot_pos = nh.subscribe("current_state_est", 100, &planning_node::GetPose, this);
        path_sub = nh.subscribe("/move_base_Quadruped/NavfnROS/plan",100,&planning_node::GetPathPoint,this);
        map_sub = nh.subscribe("projected_map_step", 1, &planning_node::CheckStep, this);
      
        path_point_pub = nh.advertise<geometry_msgs::Point>("path_point",1);
        path_point.z = 0;

        timer = nh.createTimer(ros::Rate(hz), &planning_node::PathPointPub, this);

        ROS_INFO("planning_node start");
    }
    
    //get the current position, velocity and orientation
    void GetPose(const nav_msgs::Odometry& cur_state) {
        current_position << cur_state.pose.pose.position.x, cur_state.pose.pose.position.y;
        current_velocity << cur_state.twist.twist.linear.x,cur_state.twist.twist.linear.y;

        // Extract the face direction (yaw angle) from the quaternion orientation
        geometry_msgs::Quaternion orientation = cur_state.pose.pose.orientation;
        double yaw = tf::getYaw(orientation);
        // Calculate the 2D vector based on the yaw angle
        current_direction(0) = cos(yaw);
        current_direction(1) = sin(yaw);
    }

    //get path from global planner
    void GetPathPoint(const nav_msgs::Path& path_info){
        Eigen::Vector2d point;
        Eigen::Vector2d d;
        int i;
        for(i=0; i<path_info.poses.size();i++){
            point<<path_info.poses[i].pose.position.x, path_info.poses[i].pose.position.y;
            d = (point - current_position);
            
            // constraint on distance between robot and path point
            if(d.norm() > 0.5 && d.norm() < 1.0){
                double cos_d2v;
                
                // ensure the path point is in front of robot
                if(current_direction.norm() * d.norm() != 0)
                    // Calculate the cosine value of the angle between the current robot's orientation vector and the distance vector using dot product and the magnitudes of the vectors: a * b / (|a| * |b|).
                    cos_d2v = current_direction.dot(d) / (current_direction.norm() * d.norm());
                else
                    cos_d2v = 0;
                if(cos_d2v > -std::sqrt(3)/2){
                    path_point.x = point(0);
                    path_point.y = point(1);
                    break;
                }
            }
            // If no path point that satisfies the constraint conditions is found after traversing all the path points, the current robot position will be slightly offset (by 0.01 units) along the current orientation direction to serve as the path_point.
            if(i == path_info.poses.size()-1){
                path_point.x = current_position(0) + 0.01*current_direction(0);
                path_point.y = current_position(1)+ 0.01*current_direction(1);
            }
        }
    }

    // check if there is step or slope in front
    void CheckStep(const nav_msgs::OccupancyGrid& map_info){  
 
        map_width = map_info.info.width;
        map_height = map_info.info.height;
        resolution = map_info.info.resolution;
        origin_x = map_info.info.origin.position.x;
        origin_y = map_info.info.origin.position.y;
        occupied_count= 0;
        int columns, rows;
            columns = (int) ((path_point.x - origin_x) / resolution);
            rows = (int) ((path_point.y- origin_y) / resolution);
        for(int i=-2;i<=2;i++){
            for(int j=-2;j<=2;j++){
                idx = (rows + i) * map_width + columns + j;
                occupancy = map_info.data[idx];
                if(occupancy == 100){
                    occupied_count = occupied_count + 1;
                }
            }
        }

        if(occupied_count > 18){
            path_point.z = 2;
            ROS_WARN("There is a step");
        }
        else
            path_point.z = 0;
        
    } 

    void PathPointPub(const ros::TimerEvent& t){
        path_point_pub.publish(path_point); 
    }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "planning_node");
    planning_node n;
    ros::spin();
}
