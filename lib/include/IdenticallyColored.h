#include <open3d/Open3D.h>
#include <string>

namespace gsoc
{
    std::shared_ptr<open3d::geometry::TriangleMesh> ReadGSocTestFile(std::string file_path, bool vis = false);
    void Traverse(open3d::geometry::TriangleMesh &);
} // namespace gsoc
