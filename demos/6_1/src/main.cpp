#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "VertexData.h"
#include "ShaderSource.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture2D.h"
#include "Mesh.h"

using namespace std;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location, a_uv_location, u_diffuse_texture_location;
GLuint kVBO, kEBO, kVAO;

void init_opengl()
{
    //设置错误回调
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //创建窗口
    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);
}

//file:main.cpp line:58
/// 编译、链接Shader
void compile_shader()
{
    //创建顶点Shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //编译Shader
    glCompileShader(vertex_shader);
    //创建片段Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //编译Shader
    glCompileShader(fragment_shader);
    //创建GPU程序
    program = glCreateProgram();
    //附加Shader
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    //Link
    glLinkProgram(program);
}

void GeneratorBufferObject() {
    glGenBuffers(1, &kVBO);
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    glBufferData(GL_ARRAY_BUFFER, 
            kVertexRemoveDumplicateVector.size() * sizeof(Vertex), 
            &kVertexRemoveDumplicateVector[0], GL_STATIC_DRAW);

    glGenBuffers(1, &kEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            kVertexIndexVector.size() * sizeof(unsigned short), 
            &kVertexIndexVector[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &kVAO);
    glBindVertexArray(kVAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, kVBO);

        glEnableVertexAttribArray(vpos_location);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, 
                sizeof(Vertex), 0);

        glEnableVertexAttribArray(vcol_location);
        glVertexAttribPointer(vcol_location, 3, GL_FLOAT, false, 
                sizeof(Vertex), (void *)(sizeof(float) * 3));

        glEnableVertexAttribArray(a_uv_location);
        glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, 
                sizeof(Vertex), (void *)(sizeof(float) * (3 + 4)));
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


namespace DEMO_6_1 {
int run() {
    VertexRemoveDumplicate();
    ExportMesh(string("F:\\tmp\\test.mesh"), kVertexRemoveDumplicateVector, 
            kVertexIndexVector);
    Mesh* _mesh = Mesh::loadMesh(string("F:\\tmp\\test.mesh"));
    delete _mesh;
    return 0;
}

int run2() 
{
    //file:main.cpp line:118
    //获取shader属性ID
    
    printf("im here\n");
    init_opengl();
    VertexRemoveDumplicate();
    auto _texture = Texture2D::LoadFromFile(std::string("F:\\shpic\\gpu.cpt"));
    compile_shader();
    mvp_location = glGetUniformLocation(program, "u_mvp");
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");
    a_uv_location = glGetAttribLocation(program, "a_uv");
    u_diffuse_texture_location = glGetUniformLocation(program, "u_diffuse_texture");
    float rotate_eulerAngle = 0.0f;

    //file:main.cpp line:122
    GeneratorBufferObject();
    printf("will window\n");
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        rotate_eulerAngle += 0.1;
        glm::mat4 model,view, projection, mvp;
        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f/255,77.f/255,121.f/255,1.f);
        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0,0,0)); //不移动顶点坐标;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //使用欧拉角旋转;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans*scale*rotation;
        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
        projection = glm::perspective(glm::radians(60.f),ratio,1.f,1000.f);
        mvp = projection*view*model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//开启背面剔除
            
            glBindVertexArray(kVAO);
            
            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, _texture->gl_texture_id_);
            glUniform1i(u_diffuse_texture_location, 0);

            //上传顶点数据并进行绘制
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
            glBindVertexArray(0);
            // glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete _texture;
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "end" <<std::endl;
    return 0;
}
}
