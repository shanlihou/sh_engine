#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 pos_;
    glm::vec4 color_;
    glm::vec2 uv_;

    bool operator==(Vertex const& v2) const;
};

#endif
