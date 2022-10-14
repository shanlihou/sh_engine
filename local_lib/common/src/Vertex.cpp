#include "Vertex.h"

bool Vertex::operator==(Vertex const&v2) const {
    return pos_ == v2.pos_ && color_ == v2.color_ && uv_ == v2.uv_;
}
