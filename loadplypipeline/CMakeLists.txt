cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(loadplypipeline)

find_package(PCL 1.3 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")

add_executable(loadplypipeline loadplypipeline.cpp)
target_link_libraries(loadplypipeline ${PCL_LIBRARIES})
