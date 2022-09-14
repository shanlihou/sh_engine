#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "demo_3_1.h"

// int main()
// {
//     return 0;
// }
//
int main(void)
{
    std::cout <<"hello";
    DEMO_3_1::run();
    // GLFWwindow* window;
    // /* 初始化glfw */
    // if (!glfwInit())
    //     return -1;
    // /* 创建一个Window 和 OpenGL上下文 */
    // window = glfwCreateWindow(960, 640, "Hello World", NULL, NULL);
    // if (!window)
    // {
    //     //创建失败就退出
    //     glfwTerminate();
    //     return -1;
    // }
    // /* 激活上面创建的OpenGL上下文 */
    // glfwMakeContextCurrent(window);
    // gladLoadGL();
    // /* 进入游戏引擎主循环 */
    // while (!glfwWindowShouldClose(window))
    // {
    //     /* Render here */
    //     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //     glClearColor(49.f/255,77.f/255,121.f/255,1.f);
    //     /* Swap front and back buffers */
    //     glfwSwapBuffers(window);
    //     /* 处理鼠标 键盘事件 */
    //     glfwPollEvents();
    // }
    // glfwTerminate();
    return 0;
}

// int main()
// {
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     return 0;
// }

