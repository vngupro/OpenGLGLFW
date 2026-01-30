#include "Rectangle.h"
#include <vector>

Rectangle::Rectangle(float width, float height)
{
    float hw = width / 2.0f;
    float hh = height / 2.0f;

    std::vector<float> vertices = {
        // positions         // colors           // tex coords
        -hw, -hh, 0.0f,      1.0f, 0.0f, 0.0f,    0.0f, 0.0f, // bottom-left
         hw, -hh, 0.0f,      0.0f, 1.0f, 0.0f,    1.0f, 0.0f, // bottom-right
         hw,  hh, 0.0f,      0.0f, 0.0f, 1.0f,    1.0f, 1.0f, // top-right
        -hw,  hh, 0.0f,      1.0f, 1.0f, 0.0f,    0.0f, 1.0f  // top-left
    };

    std::vector<unsigned int> indices = {
        0, 2, 1,  // first triangle CCW
        2, 3, 0   // second triangle CCW
    };

    SetupMesh(vertices, indices);
}
