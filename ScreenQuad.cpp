#include "ScreenQuad.h"
#include <vector>

ScreenQuad::ScreenQuad()
{
    std::vector<float> vertices = {
        // pos          // uv
        -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,   0.0f, 1.0f
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    SetupMesh(vertices, indices);
}
