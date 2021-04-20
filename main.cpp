#include <iostream>
#include <glad/glad.h>
#include <Shader.h>
#include <GLFW/glfw3.h>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}
//这里的坐标是屏幕坐标
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     
};
float verticeAndColor[] = {
    0.5f,-0.5f,0.0f,  1.0f,0.0f,0.0f,
    -0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
    0.0f,0.5f,0.0f,   0.0f,0.0f,1.0f,
};
const char *vertexShaderSource = 
"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 color;//顶点色\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   vertexColor = color;"
    "}\0";
const char *fragShaderSource =
 "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
    "FragColor = vec4(vertexColor,1.0);\n"
"}\0";



int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    //设置opengl版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    //向前兼容
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //告诉glad加载系统相关的函数指针地址的函数 
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"failed to  initalize GLAD"<<std::endl;
        return -1;
    }
    glViewport(0,0,640,800);
    //设置窗口大小调整回调
    glfwSetFramebufferSizeCallback(window,
    framebuffer_size_callback);
    
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1,&VBO);//申请vertex buffer obj
    glBindBuffer(GL_ARRAY_BUFFER,VBO);//vbo绑定到
    //顶点数据从cpu内存复制到gpu内存
    glBufferData(GL_ARRAY_BUFFER,sizeof(verticeAndColor),verticeAndColor,GL_STATIC_DRAW);
    //顶点 数据导入
    // glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    // glEnableVertexAttribArray(0);
    //加上顶点色的输入导入
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    //顶点色导入
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(VAO);
    // char* folder = "/Users/zhaowenpeng/git/opengl/shader/";
    Shader shader ("/Users/zhaowenpeng/git/opengl/shader/vertex.vs","/Users/zhaowenpeng/git/opengl/shader/fragment.fs");

    /* Loop until the user closes the window  渲染循环*/
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float timeValue = glfwGetTime();
        float greenValue =(sin(timeValue)/2.0f+0.5f);
        // int vertexColorLocation = glGetUniformLocation(shaderProgram,"color");
        shader.use();
        // glUniform4f(vertexColorLocation,greenValue,greenValue,greenValue,1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        /* Swap front and back buffers */
        //交换颜色缓冲
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    
    // glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
