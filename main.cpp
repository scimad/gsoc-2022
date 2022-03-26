#include <string>
#include <open3d/Open3D.h>

int main(int argc, char** argv){
    std::string filepath = "../test-data/test_mesh.ply";
    auto mesh_ptr = open3d::io::CreateMeshFromFile(filepath,true);
    open3d::visualization::DrawGeometries({mesh_ptr},"GSoC::Read Mesh");

    return 0;
}
