#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

float x_ = 0.0f;
float inc = 0.01f;

GLuint createShaderProgram()
{
    const char *vshaderSource =
            "#version 430  \n"
            "uniform float offset;\n"
            "void main(void) \n"
            "{if(gl_VertexID == 0) gl_Position = vec4(0.25+offset,-0.25+offset,0.0,1.0);"
            "else if(gl_VertexID == 1) gl_Position = vec4(-0.25+offset,-0.25-offset,0.0,1.0);"
            "else gl_Position = vec4(0.25+offset,0.25,0.0,1.0);}";
    const char *fshaderSource =
            "#version 430  \n"
            "out vec4 color; \n"
            "void main(void) \n"
            "{ if(gl_FragCoord.x < 295) color = vec4(0.1,1.0,0.0,1.0); "
            "else color = vec4(0.0,1.0,0.0,1.0);}";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vShader,1,&vshaderSource, NULL);
    glShaderSource(fShader,1,&fshaderSource, NULL);
    glCompileShader(vShader);
    glCompileShader(fShader);
    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram,fShader);
    glLinkProgram(vfProgram);
    return vfProgram;
}


void fillBuffer(GLFWwindow* w, double curTime);

void init(GLFWwindow* window)
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);

}

void display(GLFWwindow* window, double currentTime)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(1,0.1,0.45,0.1); // RGBA values 0f-1f
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);
    x_+=inc;
    if(x_>1.0f) inc = -0.01f;
    if(x_<-1.0f) inc = 0.01f;
    GLuint offsetLoc = glGetUniformLocation(renderingProgram, "offset");
    glPointSize(abs(30.0f+x_*100.0f));

    glProgramUniform1f(renderingProgram, offsetLoc,x_);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawArrays(GL_POINTS,0,1);
    glDrawArrays(GL_TRIANGLES,0,3);
   std::cout << currentTime << std::endl;
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
    if(glewInit() != GLEW_OK)
    {
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);
    init(window);


    fillBuffer(window, glfwGetTime());

    return 0;
}


void fillBuffer(GLFWwindow* w, double cTime)
{
    while(!glfwWindowShouldClose(w))
    {
        display(w,glfwGetTime());
        glfwSwapBuffers(w);
        glfwPollEvents();

    }
    glfwDestroyWindow(w);
    glfwTerminate();
}
