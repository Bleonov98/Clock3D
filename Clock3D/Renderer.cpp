#include "Renderer.h"

Renderer::Renderer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normals));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::Render()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::AddShape(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
    this->indices.insert(this->indices.end(), indices.begin(), indices.end());

    SetupMesh();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

    // vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normals));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::SetupMesh()
{
    if (vertices.size() % 3 != 0) {
        for (int i = 0; i < vertices.size() - 1; i += 3)
        {
            // edges
            glm::vec3 v1 = vertices[i + 1].Position - vertices[i].Position;
            glm::vec3 v2 = vertices[i + 2].Position - vertices[i].Position;
            glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

            // normals
            vertices[i].Normals = normal;
            vertices[i + 1].Normals = normal;
            vertices[i + 2].Normals = normal;
        }
    }
    else {
        for (int i = 0; i < vertices.size(); i += 3)
        {
            // edges
            glm::vec3 v1 = vertices[i + 1].Position - vertices[i].Position;
            glm::vec3 v2 = vertices[i + 2].Position - vertices[i].Position;
            glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

            // normals
            vertices[i].Normals = normal;
            vertices[i + 1].Normals = normal;
            vertices[i + 2].Normals = normal;
        }
    }
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
