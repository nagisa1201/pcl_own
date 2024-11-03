#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include "filesystem"
/**
 * @brief
 *  auto &point：auto 用于自动推断 point(新定义的变量)的类型，
 *  & 表示 point 是对容器中每个元素的引用。
 *  这意味着在循环中对 point 的修改将直接影响到 cloud_ptr->points 中的实际数据，而不只是副本。
    
    : 表示范围-based for 循环的语法，意为“对右侧的容器进行迭代”。

    cloud_ptr->points：这是一个指向 pcl::PointCloud<pcl::PointXYZ> 的智能指针，
    points 是该点云中的点的集合。
 */
int main()
{
    pcl::PointCloud<pcl::PointXYZ> cloud_ptr;
    cloud_ptr.width = 5;
    cloud_ptr.height = 1;
    cloud_ptr.is_dense = false;
    cloud_ptr.resize(cloud_ptr.width * cloud_ptr.height);

    for(auto &point:cloud_ptr.points)
    //
    {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }


    auto filepath = static_cast<std::string>(std::filesystem::path(__FILE__).parent_path())+"/../data/mywrite.pcd";
    pcl::io::savePCDFileASCII (filepath, cloud_ptr);
    std::cerr << "Saved " << cloud_ptr.size () << " data points to mywrite.pcd." << std::endl;

    for(const auto &point:cloud_ptr.points)
    {
        std::cout << "    " << point.x
                  << " "    << point.y
                  << " "    << point.z << std::endl;
    }



    return 0;
}