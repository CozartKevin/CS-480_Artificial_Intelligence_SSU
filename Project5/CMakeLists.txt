cmake_minimum_required(VERSION 3.15)
project(Project5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Eigen3)
include_directories(${PROJECT_SOURCE_DIR}/Eigen3)



add_executable(Project5 main.cpp ImageObject.cpp)

target_link_libraries (Project5 Eigen3::Eigen)