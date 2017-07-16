// Lingyu Zhang
// lz2494@columbia.edu
// Geon fitting project
// load all the obj files in one selected directory.
// obj to pcd to normals to fpfh to multi scale fpfh to saved pcd files.
// 2016 winter
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <iostream>  
#include <vector>  
#include <string>  
#include <dirent.h>  
#include <pcl/io/pcd_io.h>
#include <pcl/io/obj_io.h>
#include <pcl/PolygonMesh.h>
//#include <pcl/ros/conversions.h>//formROSMsg所属头文件；
#include <pcl/point_cloud.h>
#include <pcl/io/vtk_lib_io.h>//loadPolygonFileOBJ所属头文件；
//#include <pcl/visualization/pcl_visualizer.h>
using namespace pcl;
using namespace std;  
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/integral_image_normal.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/point_types.h>
#include <pcl/features/fpfh.h>
#include <pcl/common/common.h>


 std::string pcd_filename_;
void
parseCommandLine (int argc, char *argv[])
{
  std::vector<int> filenames;
  filenames = pcl::console::parse_file_extension_argument (argc, argv, ".pcd");
  if (filenames.size () != 1)
  {
    std::cout << "Filenames missing.\n";
    exit (-1);
  }

  pcd_filename_ = argv[filenames[0]];

}
   

int
main (int argc, char** argv)
{

  vector<string> objfiles;
  std::ifstream file("objfiles.txt");
  //convert txt to string to use
  while (file) {
    std::string line;
    std::getline(file, line);
    objfiles.push_back(line);
  }  

  // string plyfiles[0];
  // plyfiles[0]="sphere0.ply";
  //cout << plyfiles[1] << endl; 
  // string a = "\"" + plyfiles[1] + "\"";
  // cout << a << endl;
  for(int i = 0; i < objfiles.size(); ++i)
  {
  const std::string A = objfiles[i];
  cout << A << endl;
  cout << i << endl;
  //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);


		// pcl::PolygonMesh mesh;
  //       pcl::io::loadPolygonFile(A,mesh);
  //       pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  //       pcl::fromPCLPointCloud2(mesh.cloud, *cloud);
  //pcl::io::loadPLYFile<pcl::PointXYZ> (A, *cloud);
    parseCommandLine (argc, argv);

    // load point cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  //  pcl::io::loadPCDFile ("/media/lingyuzhang/SCHOOL/1Columbia/1Courses/ELEN_6001_AdvancedProject/2UsePCL/pyramid0source.pcd", *cloud);


if (pcl::io::loadPCDFile (pcd_filename_, *cloud) < 0)
  {
    std::cout << "Error loading model cloud." << std::endl;
    //showHelp (argv[0]);
    return (-1);
  }
  




    // if (pcl::io::loadPolygonFilePLY(A, *cloud) == -1) //* load the file
    // {
    //   PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
    //   return (-1);
    // }
    std::cout << "Loaded "
              << cloud->width * cloud->height
              << " data points from test_pcd.pcd with the following fields: "
              << std::endl;

    
    string B = objfiles[i].substr(0, objfiles[i].size() - 4);
  
    cout<< B <<endl;
    //pcl::io::savePCDFile (B + ".pcd",*cloud);

	//pcl::io::savePCDFileASCII("/Users/lingyuzhang/Spring17/2DVMM/CheckModel/CheckPoint3/Multiscale/1.Feature_ModelTraining_c++/36PipelineFPFHlingyu/build/output/"+B + ".pcd",*cloud);
// Create the normal estimation class, and pass the input dataset to it
  pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
  ne.setInputCloud (cloud);

//find the searching radius
pcl::PointCloud<pcl::PointXYZ> cloudobject;
cloudobject = *cloud;

    double max_dist = std::numeric_limits<double>::min ();
     int i_min = -1, i_max = -1;
 
     for (size_t i = 0; i < cloudobject.points.size (); ++i)
     {
       for (size_t j = i; j < cloudobject.points.size (); ++j)
       {
         // Compute the distance 

         double dist = (cloudobject.points[i].getVector4fMap () - 
                        cloudobject.points[j].getVector4fMap ()).squaredNorm ();
                  
         if (dist <= max_dist)
           continue;
 
         max_dist = dist;
         i_min = i;
         i_max = j;
       }
     }
 double R;
     if (i_min == -1 || i_max == -1)
      max_dist = std::numeric_limits<double>::min ();
 
     //pmin = cloud.points[i_min];
     //pmax = cloud.points[i_max];
     R = std::sqrt (max_dist);


cout<< R <<endl;
double r = R/30; 

//double r1 = 2*r; 
//double r2 = 3*r; 
double r1 = 4*r;
//double r4 = 5*r;
//double r5 = 6*r;
// double r6 = 7*r;
// double r7 = 8*r;

//find the searching radius




  // Create an empty kdtree representation, and pass it to the normal estimation object.
  // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree1 (new pcl::search::KdTree<pcl::PointXYZ> ());
  ne.setSearchMethod (tree1);

  // Output datasets
  pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

  // Use all neighbors in a sphere of radius 3cm
  ne.setRadiusSearch (r);
  
  // Compute the features
  ne.compute (*cloud_normals);
  //pcl::io::savePCDFile (B+ "normals.pcd", *cloud_normals);

  // Create the FPFH estimation class, and pass the input dataset+normals to it
  pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh;
  fpfh.setInputCloud (cloud);
  fpfh.setInputNormals (cloud_normals);
  // alternatively, if cloud is of tpe PointNormal, do fpfh.setInputNormals (cloud);

  // Create an empty kdtree representation, and pass it to the FPFH estimation object.
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
  //pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr tree (new pcl::KdTreeFLANN<pcl::PointXYZ> ()); -- older call for PCL 1.5-
  fpfh.setSearchMethod (tree);


  // Output datasets
  pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhsr1 (new pcl::PointCloud<pcl::FPFHSignature33> ());

  // Use all neighbors in a sphere of radius 5cm
  // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
 
  
  fpfh.setRadiusSearch (r1);
  

  // Compute the features
  fpfh.compute (*fpfhsr1);
  //cout << "fpfhs" << *fpfhs << "\n";
  // fpfhs->points.size () should have the same size as the input cloud->points.size ()*
  pcl::io::savePCDFile ( B + "fpfhr1.pcd",*fpfhsr1);

//  // Output datasets
//   pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhsr2 (new pcl::PointCloud<pcl::FPFHSignature33> ());

//   // Use all neighbors in a sphere of radius 5cm
//   // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
 
  
//   fpfh.setRadiusSearch (r2);
  

//   // Compute the features
//   fpfh.compute (*fpfhsr2);
//   //cout << "fpfhs" << *fpfhs << "\n";
//   // fpfhs->points.size () should have the same size as the input cloud->points.size ()*
//   pcl::io::savePCDFile ("/Users/lingyuzhang/Spring17/2DVMM/CheckModel/CheckPoint3/Multiscale/1.Feature_ModelTraining_c++/36PipelineFPFHlingyu/build/output/"+B + "fpfhr2.pcd",*fpfhsr2);


// // Output datasets
//   pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhsr3 (new pcl::PointCloud<pcl::FPFHSignature33> ());

//   // Use all neighbors in a sphere of radius 5cm
//   // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
 
  
//   fpfh.setRadiusSearch (r3);
  

//   // Compute the features
//   fpfh.compute (*fpfhsr3);
//   //cout << "fpfhs" << *fpfhs << "\n";
//   // fpfhs->points.size () should have the same size as the input cloud->points.size ()*
//   pcl::io::savePCDFile ("/Users/lingyuzhang/Spring17/2DVMM/CheckModel/CheckPoint3/Multiscale/1.Feature_ModelTraining_c++/36PipelineFPFHlingyu/build/output/"+B + "fpfhr3.pcd",*fpfhsr3);


// // Output datasets
//   pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhsr4 (new pcl::PointCloud<pcl::FPFHSignature33> ());

//   // Use all neighbors in a sphere of radius 5cm
//   // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
 
  
//   fpfh.setRadiusSearch (r4);
  

//   // Compute the features
//   fpfh.compute (*fpfhsr4);
//   //cout << "fpfhs" << *fpfhs << "\n";
//   // fpfhs->points.size () should have the same size as the input cloud->points.size ()*
//   pcl::io::savePCDFile ("/Users/lingyuzhang/Spring17/2DVMM/CheckModel/CheckPoint3/Multiscale/1.Feature_ModelTraining_c++/36PipelineFPFHlingyu/build/output/"+B + "fpfhr4.pcd",*fpfhsr4);

// // Output datasets
//   pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhsr5 (new pcl::PointCloud<pcl::FPFHSignature33> ());

//   // Use all neighbors in a sphere of radius 5cm
//   // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!!
 
  
//   fpfh.setRadiusSearch (r5);
  

//   // Compute the features
//   fpfh.compute (*fpfhsr5);
//   //cout << "fpfhs" << *fpfhs << "\n";
//   // fpfhs->points.size () should have the same size as the input cloud->points.size ()*
//   pcl::io::savePCDFile ("/Users/lingyuzhang/Spring17/2DVMM/CheckModel/CheckPoint3/Multiscale/1.Feature_ModelTraining_c++/36PipelineFPFHlingyu/build/output/"+B + "fpfhr5.pcd",*fpfhsr5);




  }
  // for (size_t i = 0; i < cloud->points.size (); ++i)
  //   std::cout << "    " << cloud->points[i].x
  //             << " "    << cloud->points[i].y
  //             << " "    << cloud->points[i].z << std::endl;

  return (0);





}

