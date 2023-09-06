#ifndef PARALL_H
#define PARALL_H

#include "Shape.h"

class Parallelepiped : public Shape
{
public:
	
	Parallelepiped(glm::vec3 position, glm::vec3 scale, glm::vec3 angles, float width, float length, float height, glm::vec3 color = glm::vec3(0.5f, 0.0f, 0.0f)) 
		: Shape(position, scale, angles, color) 
	{
		this->width = width, this->height = height, this->length = length;
	};

	void SetShape() override;

private:

	float width, length, height;

};

#endif