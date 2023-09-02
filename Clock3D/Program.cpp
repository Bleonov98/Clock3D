#include "Program.h"

Camera camera;
Parallelepiped* parallel;
Cylinder* cylinder;

void Program::Init()
{
	// init render tools
	shapeShader.LoadShader("vShader.vx", "fShader.ft");

	// init matrices
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 8000.0f);

	// init figures
	parallel = new Parallelepiped(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.5f, 1.0f, 0.5f);
	parallel->SetShape();

	cylinder = new Cylinder(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.2f, 3.0f, 16, glm::vec3(0.5f, 0.9f, 0.9f));
	cylinder->SetShape();
}

void Program::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_LEFT]) angleDif += angleDifSpeed * dt;
	if (this->Keys[GLFW_KEY_RIGHT]) angleDif -= angleDifSpeed * dt;
	if (this->Keys[GLFW_KEY_UP]) cylinder->SetAngle(cylinder->GetAngle() + angleDifSpeed * dt);
}

void Program::Update(float dt)
{
}

void Program::Render(float dt)
{
	DrawShape(parallel, dt);
	DrawShape(cylinder, dt);
}

void Program::DrawShape(Shape* shape, float dt)
{
	shapeShader.Use();

	shapeShader.SetMatrix4("projection", projection);
	view = camera.GetViewMatrix();
	shapeShader.SetMatrix4("view", view);

	shapeShader.SetVector3f("color", shape->GetColor());

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, shape->GetPos()); 
	model = glm::rotate(model, glm::radians(angleDif), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, shape->GetScale());	

	shapeShader.SetMatrix4("model", model);
	shape->Draw();
}
