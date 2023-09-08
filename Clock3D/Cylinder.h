#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape
{
public:

	Cylinder(glm::vec3 position, glm::vec3 scale, glm::vec3 angles, float radius, float height, int sectorsNum, glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.5f))
		: Shape(position, scale, angles, color) 
	{
		this->radius = radius, this->height = height, this->sectorsNum = sectorsNum;
	};

	void SetShape() override;
	std::vector<glm::vec3> getUnitCircleVertices();

private:

	float radius, height;
	int sectorsNum;

};

#endif // !CYLINDER_H


