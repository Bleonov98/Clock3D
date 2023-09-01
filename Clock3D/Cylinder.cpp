#include "Cylinder.h"

void Cylinder::SetShape()
{
    std::vector<glm::vec3> unitVertices = getUnitCircleVertices();

    // side vertices
    for (int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float t = 1.0f - i;                              // vertical tex coord; 1 to 0

        for (int j = 0, k = 0; j <= sectorsNum; ++j, ++k)
        {
            float ux = unitVertices[k].x;
            float uy = unitVertices[k].y;
            float uz = unitVertices[k].z;


            // position vector
            SetVertex(glm::vec3(ux * radius, uy * radius, h));
        }
    }

    // the starting index for the base/top surface
    int baseCenterIndex = (int)shapeVertices.size() / 3;
    int topCenterIndex = baseCenterIndex + sectorsNum + 1; // include center vertex

    // put base and top vertices to arrays
    for (int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float nz = -1 + i * 2;                           // z value of normal; -1 to 1

        // center point
        SetVertex(glm::vec3(0, 0, h));

        for (int j = 0, k = 0; j < sectorsNum; ++j, ++k)
        {
            float ux = unitVertices[k].x;
            float uy = unitVertices[k].y;
            // position vector
            SetVertex(glm::vec3(ux * radius, uy * radius, h));
        }
    }

    // Triangles
    int k1 = 0;                         // 1st vertex index at base
    int k2 = sectorsNum + 1;           // 1st vertex index at top

    // indices for the side surface
    for (int i = 0; i < sectorsNum; ++i, ++k1, ++k2)
    {
        // 2 triangles per sector
        // k1 => k1+1 => k2
        SetTriangle(k1, k1 + 1, k2);

        // k2 => k1+1 => k2+1
        SetTriangle(k2, k1 + 1, k2 + 1);
    }

    // indices for the base surface
    for (int i = 0, k = baseCenterIndex + 1; i < sectorsNum; ++i, ++k)
    {
        if (i < sectorsNum - 1)
        {
            SetTriangle(baseCenterIndex, k + 1, k);
        }
        else // last triangle
        {
            SetTriangle(baseCenterIndex, baseCenterIndex + 1, k);
        }
    }

    // indices for the top surface
    for (int i = 0, k = topCenterIndex + 1; i < sectorsNum; ++i, ++k)
    {
        if (i < sectorsNum - 1)
        {
            SetTriangle(topCenterIndex, k, k + 1);
        }
        else // last triangle
        {
            SetTriangle(topCenterIndex, k, topCenterIndex + 1);
        }
    }
}

// generate a unit circle on XY-plane
std::vector<glm::vec3> Cylinder::getUnitCircleVertices()
{
    const float PI = 3.1415926f;
    float sectorStep = 2 * PI / sectorsNum;
    float sectorAngle;

    std::vector<glm::vec3> unitCircleVertices;
    for (int i = 0; i <= sectorsNum; ++i)
    {
        sectorAngle = i * sectorStep;
        unitCircleVertices.push_back(glm::vec3(cos(sectorAngle), sin(sectorAngle), 0));
    }

    return unitCircleVertices;
}