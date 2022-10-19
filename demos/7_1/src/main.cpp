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
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "Texture2D.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

using namespace std;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLint mvp_location, vpos_location, vcol_location, a_uv_location;
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


void GeneratorBufferObject(shared_ptr<Mesh> mesh_ptr) {
    glGenBuffers(1, &kVBO);
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    glBufferData(GL_ARRAY_BUFFER, 
            mesh_ptr->vertexes_.size() * sizeof(Vertex), 
            &(mesh_ptr->vertexes_)[0], GL_STATIC_DRAW);

    glGenBuffers(1, &kEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            mesh_ptr->indexes_.size() * sizeof(unsigned short), 
            &(mesh_ptr->indexes_)[0], GL_STATIC_DRAW);

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


namespace DEMO_7_1 {
int run2() {
    Mesh* _mesh = Mesh::loadMesh(string("F:\\tmp\\test.mesh"));
    delete _mesh;
    return 0;
}

int run() 
{
    //file:main.cpp line:118
    //获取shader属性ID
    
    printf("im here\n");
    init_opengl();

    Material _mat;
    std::string _mat_path("material/unlit.xml");
    _mat.parse(_mat_path);

    std::shared_ptr<Mesh> _mesh(Mesh::loadMesh(string("F:\\tmp\\test.mesh")));

    mvp_location = glGetUniformLocation(_mat.shader_->program_, "u_mvp");
    vpos_location = glGetAttribLocation(_mat.shader_->program_, "a_pos");
    vcol_location = glGetAttribLocation(_mat.shader_->program_, "a_color");
    a_uv_location = glGetAttribLocation(_mat.shader_->program_, "a_uv");

    float rotate_eulerAngle = 0.0f;

    //file:main.cpp line:122
    GeneratorBufferObject(_mesh);
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
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);
        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0,0,0)); //不移动顶点坐标;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle), glm::radians(rotate_eulerAngle)); //使用欧拉角旋转;
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans*scale*rotation;
        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));
        projection = glm::perspective(glm::radians(60.f),ratio,1.f,1000.f);
        mvp = projection*view*model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(_mat.shader_->program_);
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);//开启背面剔除
            
            glBindVertexArray(kVAO);
            
            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            int _idx = 0;
            for (auto _i: _mat.textures_) {
                GLint _location = glGetUniformLocation(_mat.shader_->program_, _i.first.c_str());
                glActiveTexture(GL_TEXTURE0 + _idx);
                glBindTexture(GL_TEXTURE_2D, _i.second->gl_texture_id_);
                glUniform1i(_location, 0);
                _idx++;
            }

            //上传顶点数据并进行绘制
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
            glBindVertexArray(0);
            // glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "end" <<std::endl;
    return 0;
}
}
