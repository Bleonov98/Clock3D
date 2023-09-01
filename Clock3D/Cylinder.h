#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape
{
public:

	Cylinder(glm::vec3 position, glm::vec3 scale, float angle, float radius, float height, int sectorsNum) : Shape(position, scale, angle) {
		this->radius = radius, this->height = height, this->sectorsNum = sectorsNum;
	};

	void SetShape() override;
	std::vector<glm::vec3> getUnitCircleVertices();

private:

	float radius, height;
	int sectorsNum;

};

#endif // !CYLINDER_H


