#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <iostream>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include "std_msgs/String.h"
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>


void radar_03_call(const sensor_msgs::PointCloud2ConstPtr &cloud)
{
    std::cout << "chatterCallback " << std::endl;
    //cloud.fields[0].name;
    std::cout << cloud->data.size() << std::endl;
     //pcl::PointCloud<MmtPointXYZVT>::Ptr pcl_cloud(new pcl::PointCloud<MmtPointXYZVT>);

    pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(*cloud, *temp_cloud);
    std::cout << temp_cloud->points[0].x << std::endl;





    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    //blocks until the cloud is actually rendered
    viewer.showCloud(temp_cloud);


    while (!viewer.wasStopped())
    {

    }
    //you can also do cool processing here
    //FIXME: Note that this is running in a separate thread from viewerPsycho
    //and you should guard against race conditions yourself...

}


int main(int argc, char **argv) {
    std::cout << "Hel " << std::endl;
    ros::init(argc,argv,"radar_rec");
    ros::NodeHandle nh;

    //ros::Subscriber radar_00 = nh.subscribe("/sensor/radar_front/point_cloud_no_compensate", 10, radar_00_call);
    //ros::Subscriber radar_01 = nh.subscribe("/sensor/radar_lc/point_cloud_no_compensate", 10, radar_01_call);
    //ros::Subscriber radar_02 = nh.subscribe("/sensor/radar_rc/point_cloud_no_compensate", 10, radar_02_call);
    ros::Subscriber radar_03 = nh.subscribe("/sensor/radar_lr/point_cloud_no_compensate", 10, radar_03_call);
    //ros::Subscriber radar_04 = nh.subscribe("/sensor/radar_rr/point_cloud_no_compensate", 10, radar_04_call);
    //ros::Subscriber lidar_00 = nh.subscribe("/mb/sensor/lidar/multi_scan", 10, lidar_00_call);

    ros::spin();

    ROS_INFO("I am coming ag !");

}

