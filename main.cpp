#include <string>
#include <IdenticallyColored.h>


int main(int argc, char** argv){
    auto mesh_ptr = gsoc::ReadGSocTestFile((argc > 1)?argv[1]:"../test-data/my_mesh.ply", true);
    mesh_ptr->ComputeAdjacencyList();
    gsoc::Traverse(*mesh_ptr);
    return 0;
}
