#include "Triangle.h"
#include <vector>

Triangle::Triangle(float size)
{
    float h = size * 0.866f; // height for equilateral triangle

    std::vector<float> vertices = {
        // pos                         // color            // tex coords
         0.0f,        h / 2.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.5f, 1.0f, // top
        -size / 2.0f, -h / 2.0f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom-left
         size / 2.0f, -h / 2.0f, 0.0f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f  // bottom-right
    };

    std::vector<unsigned int> indices = {
		0, 2, 1   // CCW
    };

    SetupMesh(vertices, indices);
}