#pragma once
#include "Mesh.h"

class ScreenQuad : public Mesh
{
public:
    ScreenQuad();

private:
	void SetupMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) override;
};
