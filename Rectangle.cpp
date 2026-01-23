#include "Rectangle.h"
#include <vector>

Rectangle::Rectangle(float width, float height)
{
    float hw = width / 2.0f;
    float hh = height / 2.0f;

    std::vector<float> vertices = {
        // positions         // colors
        -hw, -hh, 0.0f,      1.0f, 0.0f, 0.0f, // bottom-left, red
         hw, -hh, 0.0f,      0.0f, 1.0f, 0.0f, // bottom-right, green
         hw,  hh, 0.0f,      0.0f, 0.0f, 1.0f, // top-right, blue
        -hw,  hh, 0.0f,      1.0f, 1.0f, 0.0f  // top-left, yellow
    };

    std::vector<unsigned int> indices = {
        0, 2, 1,  // first triangle CCW
        2, 3, 0   // second triangle CCW
    };

    SetupMesh(vertices, indices);
}
