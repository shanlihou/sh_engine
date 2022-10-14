#ifndef _SHADER_H_
#define _SHADER_H_
#include <string>
#include <glad/glad.h>


class Shader {
public:
    Shader(){};
    void loadShader(std::string &path);
    void createGPUProgram();

public:
    std::string vertex_shader_source_;
    std::string fragment_shader_source_;
    GLuint program_;
};

#endif
