#ifndef SHAPE_H
#define SHAPE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"

class Shape
{
public:

	Shape(glm::vec3 position, glm::vec3 scale, glm::vec3 angles, glm::vec3 color = glm::vec3(0.5f, 0.0f, 0.0f)) {
		this->position = position, this->scale = scale;
		this->xAngle = angles.x, this->yAngle = angles.y, this->zAngle = angles.z;
		this->color = color;
	};
	
	// render
	void SetVertex(glm::vec3 position);
	void SetTriangle(unsigned int first, unsigned int second, unsigned int third);

	virtual void SetShape() = 0;
	virtual void LoadShape(const char* fileName);

	void Draw();

	// set
	void SetPos(glm::vec3 position) { this->position = position; }
	void SetScale(glm::vec3 scale) { this->scale = scale; }
	void SetColor(glm::vec3 color) { this->color = color; }

	void SetXAngle(float xAngle) { this->xAngle = xAngle; }
	void SetYAngle(float yAngle) { this->yAngle = yAngle; }
	void SetZAngle(float zAngle) { this->zAngle = zAngle; }

	// get
	glm::vec3 GetPos() { return position; }
	glm::vec3 GetScale() { return scale; }
	glm::vec3 GetColor() { return color; }

	float GetXAngle() { return xAngle; }
	float GetYAngle() { return yAngle; }
	float GetZAngle() { return zAngle; }

	std::vector<Vertex> GetVertices() { return shapeVertices; }
	std::vector<unsigned int> GetIndices() { return shapeIndices; }

protected:

	Renderer mesh;

	glm::vec3 position, scale, color;
	float xAngle, yAngle, zAngle;

	std::vector<Vertex> shapeVertices;
	std::vector<unsigned int> shapeIndices;

};

#endif

