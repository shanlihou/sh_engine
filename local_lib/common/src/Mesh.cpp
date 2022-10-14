
#include <fstream>
#include "Mesh.h"

Mesh* Mesh::loadMesh(std::string &path) {
    std::ifstream _input_file_stream(path);
    Mesh* _mesh = new Mesh();
    _input_file_stream.read((char*)&(_mesh->file_header_), sizeof(MeshFileHead));

    Vertex _tmp_vertex;
    for (int i = 0; i < _mesh->file_header_.vertex_num_; i++) {
        _input_file_stream.read((char*)&_tmp_vertex, sizeof(Vertex));
        _mesh->vertexes_.push_back(_tmp_vertex);
    }

    unsigned short index;
    for (int i = 0; i < _mesh->file_header_.vertex_index_num_; i++) {
        _input_file_stream.read((char*)&index, sizeof(unsigned short));
        _mesh->indexes_.push_back(index);
    }

    return _mesh;
}


void ExportMesh(std::string &save_path, std::vector<Vertex> &de_dup, 
        std::vector<unsigned short> &indexes) {
    std::ofstream _out_file_stream(save_path);
    MeshFileHead _file_header;
    _file_header.type_[0] = 'm';
    _file_header.type_[1] = 'e';
    _file_header.type_[2] = 's';
    _file_header.type_[3] = 'h';

    _file_header.vertex_num_ = de_dup.size();
    _file_header.vertex_index_num_ = indexes.size();

    _out_file_stream.write((char*)(&_file_header), sizeof(_file_header));
    _out_file_stream.write((char*)(&de_dup[0]), sizeof(Vertex) * _file_header.vertex_num_);
    _out_file_stream.write((char*)(&indexes[0]), sizeof(unsigned short) * _file_header.vertex_index_num_);

    _out_file_stream.close();
}
