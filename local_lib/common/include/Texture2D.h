#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H
#include <string>
#include "glad/glad.h"

class Texture2D
{
public:
    Texture2D(): width_(0), height_(0), gl_texture_format_(0), gl_texture_id_(0), mipmap_level_(0)
    {};
    static Texture2D *LoadFromFile(std::string&);
    static void CompressImageFile(std::string&, std::string&);

public:
    int width_;
    int height_;
    int gl_texture_format_;
    int mipmap_level_;
    GLuint gl_texture_id_;//纹理ID
private:
};

struct TpcFileHead
{
    char type_[3];
    int mipmap_level_;
    int width_;
    int height_;
    int gl_texture_format_;
    int compress_size_;
};

#endif
