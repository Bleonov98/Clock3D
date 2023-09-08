#include "Program.h"

Camera camera;

Cylinder* base;
Cylinder* secondHand;
Cylinder* minuteHand;
Cylinder* hourHand;

Number* twelve;
Number* three;
Number* six;
Number* nine;

void Program::Init()
{
	// init render tools
	shapeShader.LoadShader("vShader.vx", "fShader.ft");

	// init matrices
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 2000.0f);

	// init figures
	base = new Cylinder(glm::vec3(0.0f, 0.0f, 0.04f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(90.0f, 0.0f, 0.0f), 0.2f, 0.7f, 16);
	base->SetShape();
	
	secondHand = new Cylinder(glm::vec3(-0.3f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 90.0f, 0.0f), 0.075f, 2.0f, 16, glm::vec3(0.5f, 0.0f, 0.0f));
	secondHand->SetShape();

	minuteHand = new Cylinder(glm::vec3(-0.2f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 90.0f, 0.0f), 0.075f, 1.5f, 16, glm::vec3(0.0f, 0.25f, 0.2f));
	minuteHand->SetShape();

	hourHand = new Cylinder(glm::vec3(-0.1f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 90.0f, 0.0f), 0.075f, 1.0f, 16);
	hourHand->SetShape();

	twelve = new Number(glm::vec3(0.0f, 1.5f, 0.65f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(90.0f, 0.0f, 0.0f), "12.obj");
	twelve->SetShape();

	three = new Number(glm::vec3(1.5f, -0.2f, 0.65f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(90.0f, 0.0f, 0.0f), "3.obj");
	three->SetShape();

	six = new Number(glm::vec3(0.0f, -1.5f, 0.65f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(90.0f, 0.0f, 0.0f), "6.obj");
	six->SetShape();

	nine = new Number(glm::vec3(-1.5f, -0.2f, 0.65f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(90.0f, 0.0f, 0.0f), "9.obj");
	nine->SetShape();
}

void Program::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_LEFT]) yAxisGeneral += yAxisStep * dt;
	if (this->Keys[GLFW_KEY_RIGHT]) yAxisGeneral -= yAxisStep * dt;
}

void Program::Update(float dt)
{
	SetTime();

	secondHand->SetXAngle(handStep * seconds);
	minuteHand->SetXAngle(handStep * minutes);

	if (hours > 12.0f) hours -= 12.0f;
	hourHand->SetXAngle(hourStep * hours);
}

void Program::Render(float dt)
{
	// hands
	DrawShape(secondHand, dt);
	DrawShape(minuteHand, dt);
	DrawShape(hourHand, dt);

	// nums
	DrawShape(twelve, dt);
	DrawShape(three, dt);
	DrawShape(six, dt);
	DrawShape(nine, dt);

	// details
	DrawShape(base, dt);
}

void Program::DrawShape(Shape* shape, float dt)
{
	shapeShader.Use();

	shapeShader.SetMatrix4("projection", projection);
	view = camera.GetViewMatrix();
	shapeShader.SetMatrix4("view", view);

	shapeShader.SetVector3f("color", shape->GetColor());

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(yAxisGeneral + shape->GetYAngle()), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(shape->GetXAngle() - 90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, shape->GetPos());
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
