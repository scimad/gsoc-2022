cmake_minimum_required(VERSION 3.18)
project(gsoc-22 LANGUAGES C CXX)

# Find installed Open3D, which exports Open3D::Open3D
find_package(Open3D REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(identically-colored-connected)
target_sources(identically-colored-connected PRIVATE main.cpp)
target_link_libraries(identically-colored-connected PRIVATE Open3D::Open3D Eigen3::Eigen)