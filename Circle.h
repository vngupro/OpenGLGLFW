#pragma once
#include "Mesh.h"

class Circle : public Mesh
{
public:
    Circle(float radius = 0.5f, int segments = 32);
};
