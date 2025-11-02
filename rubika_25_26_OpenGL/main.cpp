#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#define THRESOLD 0

#ifndef THRESHOLD
#include "Threshold.h"
using namespace threshold;
#endif

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubika OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    init();

    float deltaTime = 0;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        const double current_time = glfwGetTime();
        deltaTime = static_cast<float>(current_time - deltaTime);

        update();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroy();
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // Move forward
    if (glfwGetKey(window,  GLFW_KEY_UP ) == GLFW_PRESS){}
        //position += direction * deltaTime * speed;
            
    // Move backward
    if (glfwGetKey(window,  GLFW_KEY_DOWN ) == GLFW_PRESS){}
        //positIon -= direction * deltaTime * speed;
            
    // Strafe right
    if (glfwGetKey(window,  GLFW_KEY_RIGHT ) == GLFW_PRESS){}
       // position += right * deltaTime * speed;
           
    // Strafe left
    if (glfwGetKey(window,  GLFW_KEY_LEFT ) == GLFW_PRESS){}
        //position -= right * deltaTime * speed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}
