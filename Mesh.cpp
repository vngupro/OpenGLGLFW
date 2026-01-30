#include "Mesh.h"

Mesh::Mesh()
    : VAO(0)
    , VBO(0)
    , EBO(0)
    , indexCount(0)
{
}

Mesh::~Mesh()
{
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::SetupMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
{
    indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    GLsizei stride = 8 * sizeof(float);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
        (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // tex coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
        (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}