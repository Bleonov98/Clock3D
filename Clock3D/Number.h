#ifndef NUMBER_H
#define NUMBER_H

#include "Shape.h"

class Number : public Shape
{
public:

	Number(glm::vec3 position, glm::vec3 scale, glm::vec3 angles, const char* fileName) : Shape(position, scale, angles) {
		this->fileName = fileName;
	};

	void SetShape() override { LoadShape(fileName);  }

private:

	const char* fileName;

};

#endif // !NUMBER_H


