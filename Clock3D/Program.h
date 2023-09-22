#ifndef PROGRAM_H
#define PROGRAM_H

// Std
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Objects
#include "Shape.h"
#include "Parallelepiped.h"
#include "Cylinder.h"
#include "Number.h"

// Tools
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"

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
	float yAxisGeneral = 0.0f;

private:

	// objects
	Shader shapeShader;

	// settings
	int width, height, action;

	// hands, time
	float yAxisStep = 30.0f, handStep = 360.0f / 60.0f, hourStep = 360.0f / 12.0f;
	int seconds, minutes, hours;

	// view/projection transformations
	glm::mat4 projection;
	glm::mat4 view;

	~Program();

};

#endif // !PROGRAM_H




