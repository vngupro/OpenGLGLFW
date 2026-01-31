#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh
{
protected:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLsizei indexCount;

public:
    Mesh();
    virtual ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void Draw() const;

    bool hasTexture = false;

protected:
    virtual void SetupMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
};