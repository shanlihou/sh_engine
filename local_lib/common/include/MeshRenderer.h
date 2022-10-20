#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_
#include <memory>

#include <glm/glm.hpp>

#include "Material.h"
#include "Mesh.h"

using std::shared_ptr;

class MeshRenderer {
public:
    MeshRenderer(): 
        vertex_array_object_(0), 
        vertex_buffer_object_(0), 
        element_buffer_object_(0) 
    {};

    MeshRenderer& setMaterial(shared_ptr<Material>);
    MeshRenderer& setMesh(shared_ptr<Mesh>);
    MeshRenderer& setMvp(glm::mat4 mvp);
    void generatorBufferObject(GLint, GLint, GLint);

    void render();

public:
    shared_ptr<Material> material_;
    shared_ptr<Mesh> mesh_;
    glm::mat4 mvp_;
    GLuint vertex_buffer_object_;
    GLuint element_buffer_object_;
    GLuint vertex_array_object_;
};

#endif
