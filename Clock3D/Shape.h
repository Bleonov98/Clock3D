#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"

class Shape
{
public:

	Shape(glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 color = glm::vec3(0.5f, 0.0f, 0.0f)) {
		this->position = position, this->scale = scale, this->color = color, this->angle = angle;
	};
	
	void SetVertex(glm::vec3 position);
	void SetTriangle(unsigned int first, unsigned int second, unsigned int third);
	void Draw();
	virtual void SetShape() = 0;

	void SetPos(glm::vec3 position) { this->position = position; }
	void SetScale(glm::vec3 scale) { this->scale = scale; }
	void SetAngle(float angle) { this->angle = angle; }
	void SetColor(glm::vec3 color) { this->color = color; }

	glm::vec3 GetPos() { return position; }
	glm::vec3 GetScale() { return scale; }
	glm::vec3 GetColor() { return color; }

	float GetAngle() { return angle; }

	std::vector<Vertex> GetVertices() { return shapeVertices; }
	std::vector<unsigned int> GetIndices() { return shapeIndices; }

protected:

	Renderer mesh;

	glm::vec3 position, scale, color;
	float angle;

	std::vector<Vertex> shapeVertices;
	std::vector<unsigned int> shapeIndices;

};

#endif

