#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
#include "filesystem"

int main()
{
    auto r_filename=static_cast<std::string>(std::filesystem::path(__FILE__).parent_path())+"/../data/ism_test_cat.pcd"; 
    auto s_filename = static_cast<std::string>(std::filesystem::path(__FILE__).parent_path())+"/../data/my_matrix_changed.pcd";
 
    pcl::PointCloud<pcl::PointXYZ>::Ptr waitchange_ptr(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::PointCloud<pcl::PointXYZ>::Ptr changed_ptr(new pcl::PointCloud<pcl::PointXYZ>());


    auto flag = pcl::io::loadPCDFile(r_filename, *waitchange_ptr);
    if(flag==-1)
    {
        PCL_ERROR("Couldn't read file");
        return -1;
    }
    if(flag==0)
    {
        PCL_INFO("read file");
    }

//定义旋转矩阵
    float theta = 3.1415926/4;
    Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();
    transform_1(0,0) =std::cos(theta);
    transform_1(0,1) =-sin(theta);
    transform_1(1,0) =sin(theta);
    transform_1(1,1) =std::cos(theta);//前行后列
    transform_1(0,3) = 0.1;//平移x轴向
    transform_1(1,3) = 0.1;//平移y轴向
    transform_1(2,3) = 0.1;//平移z轴向
/*
            |-------> This column is the translation
    | 1 0 0 x |  \
    | 0 1 0 y |   }-> The identity 3x3 matrix (no rotation) on the left
    | 0 0 1 z |  /
    | 0 0 0 1 |    -> We do not use this line (and it has to stay 0,0,0,1)
*/
    
    pcl::transformPointCloud(*waitchange_ptr, *changed_ptr, transform_1);

    if (changed_ptr->points.empty())
    {
        PCL_ERROR("no transform point cloud");
        return -1;
    }
//保存点云
    auto filepath = static_cast<std::string>(std::filesystem::path(__FILE__).parent_path())+"/../data/mywrite.pcd";
    auto saveflag=pcl::io::savePCDFileASCII (s_filename, *changed_ptr);
    if(saveflag==-1)
    {
        PCL_ERROR("Couldn't write file %s\n",s_filename);
        return -1;
    }



//可视化
    pcl::visualization::PCLVisualizer viewer ("Matrix transformation example");
    viewer.setBackgroundColor(0.0, 0.0, 0.0);
    // pcl::visualization::PointCloudColorHandlerCustom<PointT> red(cloud2, 255, 0, 0);


    viewer.addPointCloud(waitchange_ptr, "cloud1");
    viewer.addPointCloud(changed_ptr, "cloud2");

    //pcl::visualization::PCLVisualizer 类的一个成员函数，用于设置点云的渲染属性。
    //它可以帮助用户控制点云在可视化窗口中的外观，比如点的大小、颜色、透明度等
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud1");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud2");
    viewer.spin();
    system("pause");
/*
    viewer.spin():
    这个函数是阻塞式的，它会持续运行，直到窗口关闭。它会处理所有的事件，如窗口重绘、鼠标点击等，并且在窗口关闭之前不会返回。
    使用这个函数时，程序会停在这里，等待用户操作。

    viewer.spinOnce():
    这个函数是非阻塞式的。它会处理一次事件（例如绘制窗口、处理输入等），然后立即返回。
    这样可以让程序在继续执行其他代码的同时，定期更新可视化窗口。
*/
    return 0;
}