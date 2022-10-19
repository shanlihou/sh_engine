#ifndef _SHADER_H_
#define _SHADER_H_
#include <string>
#include <glad/glad.h>
#include <map>
#include <memory>


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


class ShaderManager {
public:
    static ShaderManager* instance();
    std::shared_ptr<Shader> find(std::string&);
private:
    ShaderManager() {};
    static ShaderManager* instance_;
    std::map<std::string, std::shared_ptr<Shader>> shaders_;
};

#endif
