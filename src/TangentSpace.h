#ifndef TANGENTSPACE_H
#define TANGENTSPACE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Vertex.h"

void CalculateTangentSpace(Vertex* vertices, unsigned verticesNumber, GLuint const* indices, unsigned indicesNumber)
{
	for (unsigned int i = 0 ; i < indicesNumber ; i += 3)
	{
		Vertex& v0 = vertices[indices[i]];
		Vertex& v1 = vertices[indices[i+1]];
		Vertex& v2 = vertices[indices[i+2]];

		auto const deltaPos1 = v1.m_Position - v0.m_Position;
		auto const deltaPos2 = v2.m_Position - v0.m_Position;

		auto const deltaUV1 = v1.m_TexCoords - v0.m_TexCoords;
		auto const deltaUV2 = v2.m_TexCoords - v0.m_TexCoords;

		auto const r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		auto const Tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
		auto const Bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;


		v0.m_Tangent += Tangent;
		v1.m_Tangent += Tangent;
		v2.m_Tangent += Tangent;

//		v0.m_Bitangent +=Bitangent;
//		v1.m_Bitangent += Bitangent;
//		v2.m_Bitangent += Bitangent;
	}

	for (unsigned int i = 0 ; i < verticesNumber ; i++)
	{
		vertices[i].m_Tangent = glm::normalize(vertices[i].m_Tangent);
//		vertices[i].m_Bitangent = glm::normalize(vertices[i].m_Bitangent);

	}
}


#endif //TANGENTSPACE_H
