#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename){
    std::ifstream in(filename, std::ios::binary);
    if (in){
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

class Shader{
public:
    GLuint  ID;
    Shader (const char* vertexFile, const char* fragmentFile){
        std::string vertexCode = get_file_contents(vertexFile);
        std::string fragmentCode = get_file_contents(fragmentFile);

        const char* vertexSource = vertexCode.c_str();
        const char* fragmentSource = fragmentCode.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void activate(){
        glUseProgram(ID);
    }
    void destroy(){
        glDeleteProgram(ID);
    }

    void compileErrors(unsigned int shader, const char* type){
        GLint hasCompiled;
        char infoLog[1024];
        if (type != "PROGRAM"){
            glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE){
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
            }
        }
        else{
            glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE){
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
            }
        }
    }
};
