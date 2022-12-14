#include <fstream>
#include "Shader.h"
#include "Const.h"
#include "Utils.h"



void Shader::loadShader(std::string &path) {
    std::string _path = SHILY_UTILS::toResourcePath(path);
    std::string _vs_path = _path + ".vs";
    std::string _fs_path = _path + ".fs";
    
    std::ifstream _vs_input(_vs_path);
    vertex_shader_source_ = std::string(std::istreambuf_iterator<char>(_vs_input), 
            std::istreambuf_iterator<char>());

    std::ifstream _fs_input(_fs_path);
    fragment_shader_source_ = std::string(std::istreambuf_iterator<char>(_fs_input), 
            std::istreambuf_iterator<char>());
}
    
void Shader::createGPUProgram() {
    GLuint _vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    const char * _vertex_src = vertex_shader_source_.c_str();
    glShaderSource(_vertex_shader, 1, &_vertex_src, NULL);
    //编译Shader
    glCompileShader(_vertex_shader);
    //创建片段Shader
    GLuint _fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    const char * _fragment_src = fragment_shader_source_.c_str();
    glShaderSource(_fragment_shader, 1, &_fragment_src, NULL);
    //编译Shader
    glCompileShader(_fragment_shader);
    //创建GPU程序
    program_ = glCreateProgram();
    //附加Shader
    glAttachShader(program_, _vertex_shader);
    glAttachShader(program_, _fragment_shader);
    //Link
    glLinkProgram(program_);

}

ShaderManager* ShaderManager::instance_ = NULL;

ShaderManager* ShaderManager::instance() {
    if (instance_ == NULL) {
        instance_ = new ShaderManager();
    }

    return instance_;
}


std::shared_ptr<Shader> ShaderManager::find(std::string &path) {
    auto _ret = shaders_.find(path);
    if (_ret != shaders_.end()) {
        return _ret->second;
    }

    auto _ptr = std::make_shared<Shader>();
    _ptr->loadShader(path);
    _ptr->createGPUProgram();
    shaders_[path] = _ptr;
    return _ptr;
}


