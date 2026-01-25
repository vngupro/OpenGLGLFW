#include "ScreenQuad.h"
#include <vector>

ScreenQuad::ScreenQuad()
{
    std::vector<float> vertices = {
        // pos          // color
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // bottom-left  (red)
         0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // bottom-right (green)
         0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // top-right    (blue)
        -0.5f,  0.5f,   1.0f, 1.0f, 0.0f  // top-left     (yellow)
    };


    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    SetupMesh(vertices, indices);
}
