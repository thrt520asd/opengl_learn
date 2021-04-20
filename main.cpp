#include <iostream>
#include <glad/glad.h>
// #include <GL/glew.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}
//这里的坐标是屏幕坐标
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     
};
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   vertexColor = vec4(0.5f,0.0,0.0,1.0);"
    "}\0";
const char *fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"uniform vec4 color;\n"
"void main()\n"
"{\n"
    "FragColor = color;\n"
"}\0";
void PreDraw(){
    
}



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
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    int v_success;
    char v_infoLog[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&v_success);
    if(!v_success){
         glGetShaderInfoLog(vertexShader, 512, NULL, v_infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << v_infoLog << std::endl;
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragShaderSource,NULL);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    // glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glBindVertexArray(VAO);


    /* Loop until the user closes the window  渲染循环*/
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float timeValue = glfwGetTime();
        float greenValue =(sin(timeValue)/2.0f+0.5f);
        int vertexColorLocation = glGetUniformLocation(shaderProgram,"color");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation,greenValue,greenValue,greenValue,1.0f);
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
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
