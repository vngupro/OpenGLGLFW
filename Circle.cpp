#include "Circle.h"
#include <vector>
#include <cmath>

Circle::Circle(float radius, int segments)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    // center vertex
    vertices.insert(vertices.end(), {
        0.0f, 0.0f, 0.0f,   // position
        1.0f, 1.0f, 1.0f,   // color
        0.5f, 0.5f          // tex coord (center)
        });

    // circle perimeter
    for (int i = 0; i <= segments; ++i)
    {
        float angle = (float)i / segments * 2.0f * 3.1415926f;
        float x = cosf(angle) * radius;
        float y = sinf(angle) * radius;

        // map from [-radius, radius] → [0, 1]
        float u = (x / radius + 1.0f) * 0.5f;
        float v = (y / radius + 1.0f) * 0.5f;

        vertices.insert(vertices.end(), {
            x, y, 0.0f,      // position
            0.2f, 0.7f, 1.0f,// color
            u, v             // tex coords
            });
    }

    // triangle fan indices
    for (int i = 1; i <= segments; ++i)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    SetupMesh(vertices, indices);
}
