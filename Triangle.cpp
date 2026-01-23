#include "Triangle.h"
#include <vector>

Triangle::Triangle(float size)
{
    float h = size * 0.866f; // height for equilateral triangle

    std::vector<float> vertices = {
        // pos                   // colors
         0.0f,  h / 2.0f, 0.0f,  1.0f, 0.0f, 0.0f,        // top, red
        -size / 2.0f, -h / 2.0f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom-left, green
         size / 2.0f, -h / 2.0f, 0.0f,  0.0f, 0.0f, 1.0f  // bottom-right, blue
    };

    std::vector<unsigned int> indices = {
		0, 2, 1   // CCW
    };

    SetupMesh(vertices, indices);
}