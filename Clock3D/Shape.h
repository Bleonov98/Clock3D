#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"

class Shape
{
public:

	Shape(glm::vec3 position, glm::vec3 scale, float angle) {
		this->position = position, this->scale = scale, this->angle = angle;
	};
	
	void SetVertex(glm::vec3 position);
	void SetTriangle(unsigned int first, unsigned int second, unsigned int third);
	virtual void SetShape() = 0;

	void SetPos(glm::vec3 position) { this->position = position; }
	void SetScale(glm::vec3 scale) { this->scale = scale; }
	void SetAngle(float angle) { this->angle = angle; }

	glm::vec3 GetPos() { return position; }
	glm::vec3 GetScale() { return scale; }

	float GetAngle() { return angle; }

	std::vector<Vertex> GetVertices() { return shapeVertices; }
	std::vector<unsigned int> GetIndices() { return shapeIndices; }

protected:

	glm::vec3 position, scale;
	float angle;

	std::vector<Vertex> shapeVertices;
	std::vector<unsigned int> shapeIndices;

};

#endif

