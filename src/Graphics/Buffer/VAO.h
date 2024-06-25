#pragma once
#include "VBO.h"

class VAO{
public:
    GLuint ID;
    VAO(){
        glGenVertexArrays(1, &ID);
    }

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
        VBO.bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        VBO.unbind();
    }
    void bind(){
        glBindVertexArray(ID);
    }
    void unbind(){
        glBindVertexArray(0);
    }
    void destroy(){
        glDeleteVertexArrays(1, &ID);
    }
};
