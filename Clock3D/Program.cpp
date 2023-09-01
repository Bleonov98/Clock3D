#include "Program.h"

Camera camera;
Renderer* renderer;
Parallelepiped* parallel;
Cylinder* cylinder;

void Program::Init()
{
	// init render tools
	shapeShader.LoadShader("vShader.vx", "fShader.ft");
	renderer = new Renderer();

	// init matrices
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 8000.0f);

	// init figures
	parallel = new Parallelepiped(glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.5f, 1.0f, 0.5f);
	parallel->SetShape();
	renderer->AddShape(parallel->GetVertices(), parallel->GetIndices());

	cylinder = new Cylinder(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 1.0f, 3.0f, 16);
	cylinder->SetShape();
	renderer->AddShape(cylinder->GetVertices(), cylinder->GetIndices());
}

void Program::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_LEFT]) angleDif += angleDifSpeed * dt;
	if (this->Keys[GLFW_KEY_RIGHT]) angleDif -= angleDifSpeed * dt;
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

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, shape->GetPos()); 
	model = glm::rotate(model, glm::radians(shape->GetAngle() + angleDif), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, shape->GetScale());	

	shapeShader.SetMatrix4("model", model);
	renderer->Render();
}
