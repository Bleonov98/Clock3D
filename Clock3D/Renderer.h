#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normals;
};

class Renderer {
public:
    Renderer();

    void Render();
    void AddShape(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void SetupMesh();

    ~Renderer();

private:
    GLuint VAO, VBO, EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

};

#endif