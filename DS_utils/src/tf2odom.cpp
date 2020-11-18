

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <turtlesim/Spawn.h>
#include <iostream>
#include <cmath>
using namespace std;
double x, y, z, ww, zz, hh, ii, Aww, Azz, Ahh, Aii;
double theta;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf2odom");
    std::cout << "hello";
    ros::NodeHandle node;
    ros::Publisher odom_pub = node.advertise<nav_msgs::Odometry>("/tf/odom", 50);
    tf::TransformListener listener;

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();

    ros::Rate rate(10.0);
    while (node.ok())
    {
        tf::StampedTransform transform;
        try
        {
            //得到坐标odom和坐标base_link之间的关系
            listener.waitForTransform("t265_odom_frame", "l515_link", ros::Time(0), ros::Duration(3.0));
            listener.lookupTransform("t265_odom_frame", "l515_link",
                                     ros::Time(0), transform);
        }
        catch (tf::TransformException &ex)
        {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
        }

        x = transform.getOrigin().x();
        y = transform.getOrigin().y();
        z = transform.getOrigin().z();
        //两种不同的表示方法，来表示getRotation
        ww = transform.getRotation()[0];
        zz = transform.getRotation()[1];
        hh = transform.getRotation()[2];
        ii = transform.getRotation()[3];
        // 四元数X，Y，Z，W
        Aww = transform.getRotation().getX();
        Azz = transform.getRotation().getY();
        Ahh = transform.getRotation().getZ();
        Aii = transform.getRotation().getW();
        //theta = 2 * acos(transform.getRotation().getW()) / 3.1415926 * 180;

        //next, we'll publish the odometry message over ROS
        nav_msgs::Odometry odom;
        odom.header.stamp = current_time;
        odom.header.frame_id = "world";

        //set the position
        odom.pose.pose.position.x = x;
        odom.pose.pose.position.y = y;
        odom.pose.pose.position.z = z;
        odom.pose.pose.orientation.x = Aww;
        odom.pose.pose.orientation.y = Azz;
        odom.pose.pose.orientation.z = Ahh;
        odom.pose.pose.orientation.w = Aii;
        odom.header.stamp = transform.stamp_;
        //set the velocity
        odom.child_frame_id = "camera_pixel_link";
        odom.twist.twist.linear.x = 0;
        odom.twist.twist.linear.y = 0;
        odom.twist.twist.angular.z = 0;

        //publish the message
        odom_pub.publish(odom);

        last_time = current_time;
        rate.sleep();
    }
    return 0;
}
