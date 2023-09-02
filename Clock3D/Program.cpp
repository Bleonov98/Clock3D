#include "Program.h"

Camera camera;
Parallelepiped* base;
Cylinder* secondHand;
Cylinder* minuteHand;
Cylinder* hourHand;

void Program::Init()
{
	// init render tools
	shapeShader.LoadShader("vShader.vx", "fShader.ft");

	// init matrices
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 8000.0f);

	// init figures
	base = new Parallelepiped(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.5f, 1.0f, 0.5f);
	base->SetShape();
	
	secondHand = new Cylinder(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.2f, 3.0f, 16, glm::vec3(0.5f, 0.9f, 0.9f));
	secondHand->SetShape();

	minuteHand = new Cylinder(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.2f, 2.5f, 16, glm::vec3(0.0f, 0.5f, 0.5f));
	minuteHand->SetShape();

	hourHand = new Cylinder(glm::vec3(0.0f, 0.0f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 0.2f, 1.0f, 16, glm::vec3(0.5f, 0.5f, 0.0f));
	hourHand->SetShape();
}

void Program::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_LEFT]) yAxisGeneral += yAxisStep * dt;
	if (this->Keys[GLFW_KEY_RIGHT]) yAxisGeneral -= yAxisStep * dt;
}

void Program::Update(float dt)
{
	SetTime();

	secondHand->SetAngle(handStep * seconds);
	minuteHand->SetAngle(handStep * minutes);

	if (hours > 12.0f) hours -= 12.0f;
	hourHand->SetAngle(hourStep * hours);
}

void Program::Render(float dt)
{
	DrawShape(base, dt);
	DrawShape(secondHand, dt);
	DrawShape(minuteHand, dt);
	DrawShape(hourHand, dt);
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
	model = glm::rotate(model, glm::radians(yAxisGeneral), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(shape->GetAngle() - 90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, shape->GetScale());	

	shapeShader.SetMatrix4("model", model);
	shape->Draw();
}

void Program::SetTime()
{
	std::time_t currentTime = std::time(nullptr);

	std::tm timeinfo {};
	localtime_s(&timeinfo, &currentTime);

	seconds = static_cast<float>(timeinfo.tm_sec);
	minutes = static_cast<float>(timeinfo.tm_min);
	hours = static_cast<float>(timeinfo.tm_hour);
}
