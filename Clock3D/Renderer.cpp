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
    std::vector<glm::vec3> vertexNormals(vertices.size(), glm::vec3(0.0f));

    for (int i = 0; i < indices.size(); i += 3)
    {
        int index1 = indices[i];
        int index2 = indices[i + 1];
        int index3 = indices[i + 2];

        glm::vec3 v1 = vertices[index1].Position;
        glm::vec3 v2 = vertices[index2].Position;
        glm::vec3 v3 = vertices[index3].Position;

        glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

        vertexNormals[index1] += normal;
        vertexNormals[index2] += normal;
        vertexNormals[index3] += normal;
    }

    for (int i = 0; i < vertices.size(); ++i)
    {
        vertices[i].Normals = glm::normalize(vertexNormals[i]);
    }
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
