#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H
#include <string>
class Texture2D
{
public:
    Texture2D() {};
    static Texture2D *LoadFromFile(std::string&);

public:
    int width_;
    int height_;
    int gl_texture_format_;

private:
};

#endif
