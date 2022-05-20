#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void init(GLFWwindow* window){}

void display(GLFWwindow* window, double currentTime)
{

    glClearColor(0.1,0.1,0.1,1);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    if(!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
    GLFWwindow* window = glfwCreateWindow(500,600, "Hello world!",NULL,NULL);
    glfwMakeContextCurrent(window);
    /*
    if(glewInit() != GLEW_OK)
    {
        exit(EXIT_FAILURE);
    }*/
    glfwSwapInterval(1);
    init(window);
    while(!glfwWindowShouldClose(window))
    {
        display(window,glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
