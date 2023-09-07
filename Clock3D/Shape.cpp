#include "Shape.h"

void Shape::SetVertex(glm::vec3 position)
{
	Vertex vertex;
	vertex.Position = position;
	shapeVertices.push_back(vertex);
}

void Shape::SetTriangle(unsigned int first, unsigned int second, unsigned int third)
{
	shapeIndices.push_back(first);
	shapeIndices.push_back(second);
	shapeIndices.push_back(third);
}

void Shape::Draw()
{
	mesh.Render();
}

glm::vec3 Shape::GetVertexFromStringStream(std::istringstream& str)
{
    glm::vec3 vertex;

    if (!(str >> vertex.x >> vertex.y >> vertex.z)) {
        std::cout << "vertex loading failed";
    }

    return vertex;
}

void Shape::LoadShapeFromFile(const char* fileName)
{
    std::string filePath("../models/");
    filePath += fileName;

    std::ifstream iStream(fileName);

    if (!iStream.is_open()) {
        std::cout << "Object file wasn't opened";
        return;
    }

    std::string line;
    while (std::getline(iStream, line))
    {

        if (line.substr(0, 2) == "v ") {

            std::istringstream v(line.substr(2));

            glm::vec3 vert = GetVertexFromStringStream(v);

            Vertex vertex;
            vertex.Position = vert;
            shapeVertices.push_back(vertex);
        }
        else if (line.substr(0, 2) == "f ") {

            std::istringstream ss(line.substr(2));
            std::string str = ss.str();

            int indexCnt = 1;

            for (int i = 0; i < str.size(); ++i)
            {
                if (str[i] == ' ') {
                    indexCnt++;
                }
                if (str[i] == '/') {
                    str[i] = ' ';
                }
            }
            
            std::istringstream v(str);

            for (int i = 0; i < indexCnt; ++i)
            {
                GLuint a, b, c;

                v >> a >> b >> c;

                shapeIndices.push_back(a);
                shapeIndices.push_back(b);
                shapeIndices.push_back(c);
            }
            
        }

    }

    mesh.AddShape(shapeVertices, shapeIndices);
}