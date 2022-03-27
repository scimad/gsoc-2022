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
        while (!unvisited_vertices.empty())
        {   
            int vidx = *(unvisited_vertices.begin());
            std::cout << "Checking for vert " << vidx << std::endl;
            if (unvisited_vertices.count(vidx))
            {
                std::queue<int> next_connected;
                next_connected.push(vidx);
                while (!next_connected.empty())
                {
                    int vert = next_connected.front();
                    next_connected.pop();
                    if (!unvisited_vertices.count(vert)){
                        continue;
                    }
                    unvisited_vertices.erase(vert);
                    std::cout << " Now I have visited vert " << vert << "." << std::endl;
                    auto adj_l = mesh.adjacency_list_[vert];
                    for (auto adj_v : adj_l){
                        if (unvisited_vertices.count(adj_v)){
                            next_connected.emplace(adj_v);
                        }
                    }
                }
            }
        }
    }
} // namespace gsoc