#ifndef _MESH_H_
#define _MESH_H_
#include <string>
#include <vector>
#include "Vertex.h"


struct MeshFileHead {
    char type_[4];
    int vertex_num_;
    int vertex_index_num_;
};

class Mesh {
public:
    Mesh() {};

    static Mesh* loadMesh(std::string &);   

    MeshFileHead file_header_;
    std::vector<Vertex> vertexes_;
    std::vector<unsigned short> indexes_;
};


void ExportMesh(std::string&, std::vector<Vertex>&, std::vector<unsigned short>&);

#endif
