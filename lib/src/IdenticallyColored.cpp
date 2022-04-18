#include "IdenticallyColored.h"
#include <queue>
#include <set>

namespace gsoc
{

    std::shared_ptr<open3d::geometry::TriangleMesh> ReadGSocTestFile(std::string file_path, bool vis)
    {
        auto mesh_ptr = open3d::io::CreateMeshFromFile(file_path, false);
        if (vis)
        {
            open3d::visualization::Draw({mesh_ptr}, "GSoC::Read Mesh");
        }
        return mesh_ptr;
    }

    void Traverse(open3d::geometry::TriangleMesh &mesh)
    {
        if (!mesh.HasAdjacencyList())
        {
            mesh.ComputeAdjacencyList();
        }
        std::set<int> unvisited_vertices;
        for (int i = 0; i < mesh.vertices_.size(); ++i) {
            unvisited_vertices.emplace(i);
        }
        std::vector<Eigen::Vector3d> colors;

        // icccs: identically connected colored components [[The] [final] [result]]
        // this can be vector because vidx guarantes that the order of smallest element is ascending
        // but since we are checking for colors as well now, we need to use set again!
        std::set<std::set<int>> icccs;
        while (!unvisited_vertices.empty())
        {
            int vidx = *(unvisited_vertices.begin());

            std::queue<int> connected_queue_dfs;
            connected_queue_dfs.push(vidx);

            //is using hashtable for uint8 (along with open3d::utility::ColorToUint8) better than using that for double???
            std::unordered_map<Eigen::Vector3d, std::set<int>, open3d::utility::hash_eigen<Eigen::Vector3d>> v_with_same_color;

            while (!connected_queue_dfs.empty())
            {
                int vert = connected_queue_dfs.front();
                connected_queue_dfs.pop();
                v_with_same_color[mesh.vertex_colors_[vert]].emplace(vert);
                unvisited_vertices.erase(vert);
                for (auto adj_v : mesh.adjacency_list_[vert]){
                    if (unvisited_vertices.count(adj_v)){
                        connected_queue_dfs.emplace(adj_v);
                    }
                }
            }
            for (auto c_v_map : v_with_same_color){
                icccs.emplace(c_v_map.second);
            }                
        } //Completed visiting all vertices

        std::cout << "Printing result: "<< std::endl;       
        for (auto icc : icccs){
            for (auto v : icc){
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }
    void Test(){
    }
} // namespace gsoc
