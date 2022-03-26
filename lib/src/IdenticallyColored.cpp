#include "IdenticallyColored.h"

namespace gsoc{

open3d::geometry::TriangleMesh& ReadGSocTestFile(std::string file_path){
    auto mesh_ptr = open3d::io::CreateMeshFromFile(file_path,true);
    open3d::visualization::DrawGeometries({mesh_ptr},"GSoC::Read Mesh");
    return *mesh_ptr;
}

}  // namespace gsoc