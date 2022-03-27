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
        // for (auto v: mesh.vertices_){ //vector of eigen3
        //     std::cout << "v: " << v << std::endl;
        // }

        // for (auto t: mesh.triangles_){ //vector of eigen3
        //     std::cout << "t: " << t << std::endl;
        // }

        // size_t i = 0;
        // for (auto adj: mesh.adjacency_list_){//vector of unordered_set
        //     std::cout << "adj of v: " << i++ << " are:" << std::endl;
        //     for (auto adj_v: adj){
        //         std::cout << adj_v << std::endl;
        //     }
        // }

        if (!mesh.HasAdjacencyList())
        {
            mesh.ComputeAdjacencyList();
        }
        std::set<int> visited_vertices; // std::vector<int> visited_vertices(mesh.vertices_.size());
        std::queue<int> next;
        // std::cout << "Traversing" << std::endl;
        // std::unordered_set<Eigen::Vector3d, std::hash<Eigen::Vector3d>> uniq_colors;
        std::vector<Eigen::Vector3d> colors;
        for (int vidx = 0; vidx < mesh.vertices_.size(); vidx++)
        {   
            std::cout << "Checking for vert " << vidx << std::endl;
            if (visited_vertices.count(vidx) == 0)
            {
                std::cout << "vert " << vidx << " has not been visited." << std::endl;
                next.push(vidx);
                // now scrutinize the elements of queue
                while (!next.empty())
                {
                    int vert = next.front();
                    
                    // Note 1: It means now we have visited that vertex
                    next.pop();
                    visited_vertices.emplace(vert);
                    std::cout << " Now I have visited vert " << vert << "." << std::endl;
                    // End of note 1
                    auto adj_l = mesh.adjacency_list_[vert];
                    for (auto adj_v : adj_l){
                        if (visited_vertices.count(adj_v) == 0){
                            next.emplace(adj_v);
                        }
                    }
                }
            }else{
                std::cout << "vert " << vidx << " has already been visited." << std::endl;
            }
        }
    }
} // namespace gsoc