#include "ScreenQuad.h"
#include <vector>

ScreenQuad::ScreenQuad()
{
    std::vector<float> vertices = {
        // pos          // color           // tex coords
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top-right
        -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top-left
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    SetupMesh(vertices, indices);
}

void ScreenQuad::SetupMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
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

    GLsizei stride = 7 * sizeof(float);

    // position (vec2)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // color (vec3)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride,
        (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // tex coords (vec2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride,
        (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}