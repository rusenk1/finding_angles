#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>
#include <iostream>

  geometry_msgs::TransformStamped transformStamped;

void callback(const nav_msgs::Odometry::ConstPtr& msg){

  transformStamped.child_frame_id = "base_laser_link";
  transformStamped.header.frame_id = "world";
  transformStamped.transform.translation.x= msg->pose.pose.position.x;
  transformStamped.transform.translation.y=msg->pose.pose.position.y;
  transformStamped.transform.translation.z=msg->pose.pose.position.z;
  transformStamped.transform.rotation = msg->pose.pose.orientation;
}

using namespace std;



int main(int argc, char **argv)
{
  ros::init(argc,argv, "laser_broadcaster_node");
  ros::NodeHandle n;
  tf2_ros::TransformBroadcaster odometry_broadcaster;
  ros::Rate rate(10);

ros::Subscriber sub = n.subscribe("/base_pose_ground_truth",10,callback);


while(n.ok())

{
    transformStamped.header.stamp = ros::Time::now();
  odometry_broadcaster.sendTransform(transformStamped);
   std::cout << "x: " <<transformStamped.transform.translation.x <<","
             << " y : " << transformStamped.transform.translation.y << "," 
             << "z :"  <<transformStamped.transform.translation.z << std::endl;
  ros::spinOnce();
  rate.sleep();

}


return 0;
}
