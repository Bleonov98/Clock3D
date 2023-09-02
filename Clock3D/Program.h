#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>


#include "Renderer.h"
#include "Shape.h"
#include "Parallelepiped.h"
#include "Cylinder.h"
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

	void SetTime();

	bool Keys[1024], KeysProcessed[1024];

private:

	// objects
	Shader shapeShader;

	// settings
	int width, height, action;

	// hands, time
	float yAxisGeneral = 90.0f, yAxisStep = 30.0f, handStep = 360.0f / 60.0f, hourStep = 360.0f / 12.0f;
	float seconds, minutes, hours;

	// view/projection transformations
	glm::mat4 projection;
	glm::mat4 view;

};

#endif // !PROGRAM_H




