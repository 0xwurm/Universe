#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader/shader.h"
#include "Buffer/VAO.h"
#include "Buffer/EBO.h"
#include "../Math/trig.h"

void init_gl(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

class GraphicsUnit{
public:
    Shader* shader;
    GLFWwindow* window;

    GraphicsUnit(){
        window = glfwCreateWindow(800, 800, "Universe", nullptr, nullptr);
        glfwMakeContextCurrent(window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glViewport(0, 0, 800, 800);

        shader = new Shader{"../src/Graphics/Shader/default.vert", "../src/Graphics/Shader/default.frag"};
    }

    void draw_square(float x, float y, float radius){
        GLfloat vertices[] =
                {
                        x - radius, y - radius, 0.0f,
                        x + radius, y + radius, 0.0f,
                        x + radius, y - radius, 0.0f,
                        x - radius, y + radius, 0.0f
                };
        GLuint indices[] =
                {
                        0, 2, 3,
                        1, 2, 3
                };

        VAO vao;
        vao.bind();

        VBO vbo(vertices, sizeof(vertices));
        EBO ebo(indices, sizeof(indices));

        vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 3 * sizeof(float), (void*)0);

        vao.unbind();
        vbo.unbind();
        ebo.unbind();

        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        vao.destroy();
        vbo.destroy();
        ebo.destroy();
    }

    void draw_circle(float x, float y, float radius){
        int Nvertices = 20;

        float vertices[(Nvertices+1)*3];
        unsigned int indices[Nvertices*3];

        vertices[0] = x;
        vertices[1] = y;
        vertices[2] = 0;
        for (unsigned int i=0; i<Nvertices; i++) {
            float theta = 2*3.1415f*(float)i/(float)(Nvertices);
            vertices[3*(i+1) + 0] = cos(theta) * radius + x;
            vertices[3*(i+1) + 1] = sin(theta) * radius + y;
            vertices[3*(i+1) + 2] = 0;

            indices[3*i + 0] = 0;
            indices[3*i + 1] = 1+i;
            indices[3*i + 2] = (1+i)%Nvertices + 1;
        }
        VAO vao;
        vao.bind();

        VBO vbo(vertices, sizeof(vertices));
        EBO ebo(indices, sizeof(indices));

        vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 3 * sizeof(float), (void*)0);

        vao.unbind();
        vbo.unbind();
        ebo.unbind();

        vao.bind();

        glDrawElements(GL_TRIANGLES, 3*Nvertices, GL_UNSIGNED_INT, 0);

        vao.destroy();
        vbo.destroy();
        ebo.destroy();
    }
};

