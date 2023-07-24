//这里是按照kitti写的,自己的数据集需要改一下
#include "utility.h"
void path_save(nav_msgs::Odometry odomAftMapped ){
 
	    //保存轨迹，path_save是文件目录,txt文件提前建好,/home/xxx/xxx.txt,
   			std::ofstream pose1("/home/gxk/catkin_ws/SLAM/Lio_sam/lio_path.txt", std::ios::app);
			pose1.setf(std::ios::scientific, std::ios::floatfield);
			pose1.precision(9);
      //KITTI
			// static double timeStart = odomAftMapped.header.stamp.toSec();
			// auto T1 =ros::Time().fromSec(timeStart) ;
      //       pose1<< odomAftMapped.header.stamp -T1<< " "
      //         << -odomAftMapped.pose.pose.position.y << " "
      //         << odomAftMapped.pose.pose.position.z << " "
      //         << odomAftMapped.pose.pose.position.x << " "
      //         << odomAftMapped.pose.pose.orientation.x << " "
      //         << odomAftMapped.pose.pose.orientation.y << " "
      //         << odomAftMapped.pose.pose.orientation.z << " "
      //         << odomAftMapped.pose.pose.orientation.w << std::endl;
			// pose1.close();
      //自己的数据集
       static double timeStart = odomAftMapped.header.stamp.toSec();
			//auto T1 =ros::Time().fromSec(timeStart) ;
            pose1<< odomAftMapped.header.stamp << " "
              << odomAftMapped.pose.pose.position.x << " "
              << odomAftMapped.pose.pose.position.y << " "
              << odomAftMapped.pose.pose.position.z << " "
              << odomAftMapped.pose.pose.orientation.x << " "
              << odomAftMapped.pose.pose.orientation.y << " "
              << odomAftMapped.pose.pose.orientation.z << " "
              << odomAftMapped.pose.pose.orientation.w << std::endl;
			pose1.close();
            
}
 
int main(int argc, char **argv){
    ros::init(argc, argv, "path_save");
    ros::NodeHandle nh;
    ros::Subscriber save_path = nh.subscribe<nav_msgs::Odometry>("/lio_sam/mapping/odometry_incremental",     100, path_save);	    //保存轨迹，a_loam直接订阅话题/aft_mapped_to_init。
 
    ros::spin();
     }
     /*轨迹文件的时间戳得按(xxx.header.stamp -T1)这样写，保存的是当前时间与第一帧位置时间的差值，因为Kitti真值的轨迹时间戳是这样保存的，与真值时间戳不同步之后没法评估。
     数据的z、y、z写入顺序是人为的将坐标轴与Kitti数据集的对齐了（也可以按原来的写，或者用左乘外参矩阵进行调整，因为之后会用evo按时间戳对齐进行评估），
     如下图一KItti真值是x_z轴的，你跑出来可能是横着的，但是只要时间戳没问题你还是可以把它们对齐（图二）。对齐命令如下，具体评估可以看以下博客
————————————————
版权声明：本文为CSDN博主「李97」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_62456310/article/details/129478168*/