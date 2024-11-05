#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_cloud.h>

int main()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filter_ptr (new pcl::PointCloud<pcl::PointXYZ>);

//填充 
    cloud_ptr->width  = 5;
    cloud_ptr->height = 1;
    cloud_ptr->points.resize (cloud_ptr->width * cloud_ptr->height);
    
  for(auto& point: *cloud_ptr)
  {
    point.x = 1024 * rand () / (RAND_MAX + 1.0f);
    point.y = 1024 * rand () / (RAND_MAX + 1.0f);
    point.z = 1024 * rand () / (RAND_MAX + 1.0f);
  }
    for (const auto& point: *cloud_ptr)
    std::cerr << "    " << point.x << " "
                        << point.y << " "
                        << point.z << std::endl;

//创建滤波器对象
    pcl::PassThrough<pcl::PointXYZ> pass;//数据类型包括xyz坐标

    pass.setInputCloud (cloud_ptr);//输入点云
    pass.setFilterFieldName ("z");//表示过滤将基于点云中 z 坐标的值
    pass.setFilterLimits (0.0, 1.0);//指定仅保留 z 值在 0.0 到 1.0（包括边界）之间的点
    pass.filter (*cloud_filter_ptr);//执行过滤操作，并将结果存储在 cloud_filter_ptr 中


    pcl::visualization::PCLVisualizer viewer ("Simple Cloud Viewer");
    viewer.setBackgroundColor(0.0, 0.0, 0.0);
    viewer.addPointCloud(cloud_filter_ptr, "cloud_filter_ptr");
//白加了，么杯也看不到


    std::cerr << "Cloud after filtering: " << std::endl;
    for (const auto& point: *cloud_filter_ptr)
    std::cerr << "    " << point.x << " "
                        << point.y << " "
                        << point.z << std::endl;

    viewer.spin();
    system("pause");

    return (0);



}