#ifndef PARALL_H
#define PARALL_H

#include "Shape.h"

class Parallelepiped : public Shape
{
public:
	
	Parallelepiped(glm::vec3 position, glm::vec3 scale, float angle, float width, float length, float height) : Shape(position, scale, angle) {
		this->width = width, this->height = height, this->length = length;

		SetShape();
	};

	void SetShape() override;

private:

	float width, length, height;

};

#endif