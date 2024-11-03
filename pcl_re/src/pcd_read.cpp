#include <iostream>
#include "filesystem"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int main(int argc, char **argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ptr(new pcl::PointCloud<pcl::PointXYZ>);
    //此处已经进行了初始化
    auto file_path1=static_cast<std::string>(std::filesystem::path(__FILE__).parent_path())+"/../data/test_pcd.pcd";

    auto check=pcl::io::loadPCDFile(file_path1, *cloud_ptr);
    
    if(check==-1)
    {
        std::cout << "No file found." << std::endl;
        return -1;
    }   



    std::cout << "Loaded "
              << cloud_ptr->width * cloud_ptr->height
              << " data points from test_pcd.pcd with the following fields: "
              << std::endl;
    

    for (size_t i = 0; i < cloud_ptr->points.size(); ++i)
        std::cout << "    " << cloud_ptr->points[i].x
                  << " " << cloud_ptr->points[i].y
                  << " " << cloud_ptr->points[i].z << std::endl;

    return (0);
}
