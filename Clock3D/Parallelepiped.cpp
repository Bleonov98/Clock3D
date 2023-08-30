#include "Parallelepiped.h"

void Parallelepiped::SetShape()
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	float halfLength = length / 2.0f;

	// Vertices
	SetVertex(glm::vec3(position.x - halfLength, position.y - halfHeight, position.z + halfWidth));
	SetVertex(glm::vec3(position.x - halfLength, position.y + halfHeight, position.z + halfWidth));
	SetVertex(glm::vec3(position.x + halfLength, position.y + halfHeight, position.z + halfWidth));
	SetVertex(glm::vec3(position.x + halfLength, position.y - halfHeight, position.z + halfWidth));

	SetVertex(glm::vec3(position.x - halfLength, position.y - halfHeight, position.z - halfWidth));
	SetVertex(glm::vec3(position.x - halfLength, position.y + halfHeight, position.z - halfWidth));
	SetVertex(glm::vec3(position.x + halfLength, position.y + halfHeight, position.z - halfWidth));
	SetVertex(glm::vec3(position.x + halfLength, position.y - halfHeight, position.z - halfWidth));

	// face triangle
	SetTriangle(0, 1, 2);
	SetTriangle(0, 2, 3);

	// back triangle
	SetTriangle(4, 5, 6);
	SetTriangle(4, 6, 7);
	
	// left-side triangles
	SetTriangle(0, 1, 4);
	SetTriangle(4, 5, 1);

	// right-side triangles
	SetTriangle(2, 3, 7);
	SetTriangle(2, 6, 7);

	// top triangles
	SetTriangle(1, 2, 5);
	SetTriangle(5, 6, 2);

	// bot triangles
	SetTriangle(0, 4, 7);
	SetTriangle(0, 3, 7);
	
}
