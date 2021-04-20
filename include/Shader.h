#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    /* data */
public:
    unsigned int ID;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
        //开始读取文件
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream,fShaderStream;
            vShaderStream<<vShaderFile.rdbuf();
            fShaderStream<<fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        //读取文件完毕，开始解析shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader,1,&vShaderCode,NULL);
        glCompileShader(vertexShader);
        int v_success;
        char v_infoLog[512];
        glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&v_success);
        if(!v_success){
            glGetShaderInfoLog(vertexShader, 512, NULL, v_infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << v_infoLog << std::endl;
        }
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader,1,&fShaderCode,NULL);
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
        ID = shaderProgram;

    }
    void use(){
        glUseProgram(ID);
    }
    void setBool(const std::string &name ,bool value) const{
        glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
    }
    bool setint(const std::string &name,int value) const{
        glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
    }
    bool setFloat(const std::string &name, float value) const{
        glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
    }
    ~Shader(){
        glDeleteShader(ID);
    }
};

#endif
