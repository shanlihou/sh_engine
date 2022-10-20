#include "MeshRenderer.h"
#include "Vertex.h"

MeshRenderer& MeshRenderer::setMaterial(shared_ptr<Material> mat) {
    material_ = mat;
    return *this;
}


MeshRenderer& MeshRenderer::setMesh(shared_ptr<Mesh> mesh) {
    mesh_ = mesh;
    return *this;
}


MeshRenderer& MeshRenderer::setMvp(glm::mat4 mvp) {
    mvp_ = mvp;
    return *this;
}


void MeshRenderer::generatorBufferObject(GLint vpos, GLint vcolor, GLint uv) {
    glGenBuffers(1, &vertex_buffer_object_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
    glBufferData(GL_ARRAY_BUFFER, 
            mesh_->vertexes_.size() * sizeof(Vertex), 
            &(mesh_->vertexes_)[0], GL_STATIC_DRAW);

    glGenBuffers(1, &element_buffer_object_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            mesh_->indexes_.size() * sizeof(unsigned short), 
            &(mesh_->indexes_)[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertex_array_object_);
    glBindVertexArray(vertex_array_object_);
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);

        glEnableVertexAttribArray(vpos);
        glVertexAttribPointer(vpos, 3, GL_FLOAT, false, 
                sizeof(Vertex), 0);

        glEnableVertexAttribArray(vcolor);
        glVertexAttribPointer(vcolor, 3, GL_FLOAT, false, 
                sizeof(Vertex), (void *)(sizeof(float) * 3));

        glEnableVertexAttribArray(uv);
        glVertexAttribPointer(uv, 2, GL_FLOAT, false, 
                sizeof(Vertex), (void *)(sizeof(float) * (3 + 4)));
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshRenderer::render() {
    GLuint _program = material_->shader_->program_;

    if (vertex_array_object_ == 0) {
        GLint _vpos = glGetAttribLocation(_program, "a_pos");
        GLint _vcolor = glGetAttribLocation(_program, "a_color");
        GLint _uv = glGetAttribLocation(_program, "a_uv");
        
        generatorBufferObject(_vpos, _vcolor, _uv);
    }

    glUseProgram(_program);
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);//开启背面剔除
        
        glUniformMatrix4fv(glGetUniformLocation(_program, "u_mvp"), 1, GL_FALSE, &mvp_[0][0]);

        int _idx = 0;
        for (auto _i: material_->textures_) {
            GLint _location = glGetUniformLocation(material_->shader_->program_, _i.first.c_str());
            glActiveTexture(GL_TEXTURE0 + _idx);
            glBindTexture(GL_TEXTURE_2D, _i.second->gl_texture_id_);
            glUniform1i(_location, 0);
            _idx++;
        }

        glBindVertexArray(vertex_array_object_);
        {
            glDrawElements(GL_TRIANGLES, mesh_->indexes_.size(), GL_UNSIGNED_SHORT, 0);
        }
        glBindVertexArray(0);
    }
}

