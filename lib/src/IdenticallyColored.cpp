#include "IdenticallyColored.h"
#include <queue>
#include <set>
#include <functional>

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
        std::set<std::set<int>> iccps;   //identically connected colored components [[The] [final] [result]]
        while (!unvisited_vertices.empty())
        {   
            int vidx = *(unvisited_vertices.begin());
            std::cout << "Checking for vert " << vidx << std::endl;
            if (unvisited_vertices.count(vidx))
            {
                std::queue<int> connected_queue_dfs;
                connected_queue_dfs.push(vidx);
                std::set<int> connected_component;
                while (!connected_queue_dfs.empty())
                {
                    int vert = connected_queue_dfs.front();
                    connected_queue_dfs.pop();
                    connected_component.emplace(vert);
                    if (!unvisited_vertices.count(vert)){
                        continue;
                    }
                    unvisited_vertices.erase(vert);
                    std::cout << " Now I have visited vert " << vert << "." << std::endl;
                    auto adj_l = mesh.adjacency_list_[vert];
                    for (auto adj_v : adj_l){
                        if (unvisited_vertices.count(adj_v)){
                            connected_queue_dfs.emplace(adj_v);
                        }
                    }
                }
                std::cout << "The new connected component has " << connected_component.size() <<"vertices."<< std::endl;
            }
        }
    }

    void Test(){
    }
} // namespace gsoc