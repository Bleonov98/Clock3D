#include "Shape.h"

void Shape::SetVertex(glm::vec3 position)
{
	Vertex vertex;
	vertex.Position = position;
	shapeVertices.push_back(vertex);
}

void Shape::SetTriangle(unsigned int first, unsigned int second, unsigned int third)
{
	shapeIndices.push_back(first);
	shapeIndices.push_back(second);
	shapeIndices.push_back(third);
}

void Shape::LoadShape(const char* fileName)
{
	mesh.LoadShapeFromFile(fileName);
}

void Shape::Draw()
{
	mesh.Render();
}
