#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include "Renderer.h"
#include "Shape.h"
#include "Parallelepiped.h"
#include "Camera.h"

class Program
{
public:

	Program(int width, int height) {
		this->width = width, this->height = height;
	};

	void Init();

	void ProcessInput(float dt);
	void Update(float dt);

	void Render(float dt);
	void DrawShape(Shape* shape, float dt);

	bool Keys[1024], KeysProcessed[1024];

private:

	// settings
	int width, height, action;
	float angleDif = 0, angleDifSpeed = 30.0f;
	Shader shapeShader;

	// view/projection transformations
	glm::mat4 projection;
	glm::mat4 view;

};

#endif // !PROGRAM_H




