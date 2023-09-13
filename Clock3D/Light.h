#ifndef LIGHT_H
#define LIGHT_H

#include "Renderer.h"

class Light
{
public:

	Light(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 color = glm::vec3(0.9f)) {
		this->position = position;
		this->color = color;
	};

	void SetPosition(glm::vec3 position) { this->position = position; }
	void SetColor(glm::vec3 color) { this->color = color; }

	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetColor() { return color; }

private:

	glm::vec3 color, position;

};


#endif // !LIGHT_H



