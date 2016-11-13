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

		glm::vec3 Edge1 = v1.m_Position - v0.m_Position;
		glm::vec3 Edge2 = v2.m_Position - v0.m_Position;

		float DeltaU1 = v1.m_TexCoords.x - v0.m_TexCoords.x;
		float DeltaV1 = v1.m_TexCoords.y - v0.m_TexCoords.y;
		float DeltaU2 = v2.m_TexCoords.x - v0.m_TexCoords.x;
		float DeltaV2 = v2.m_TexCoords.y - v0.m_TexCoords.y;

		float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

		glm::vec3 Tangent, Bitangent;

		Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
		Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
		Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

		Bitangent.x = f * (-DeltaU2 * Edge1.x - DeltaU1 * Edge2.x);
		Bitangent.y = f * (-DeltaU2 * Edge1.y - DeltaU1 * Edge2.y);
		Bitangent.z = f * (-DeltaU2 * Edge1.z - DeltaU1 * Edge2.z);

		v0.m_Tangent += Tangent;
		v1.m_Tangent += Tangent;
		v2.m_Tangent += Tangent;
	}

	for (unsigned int i = 0 ; i < verticesNumber ; i++)
	{
		vertices[i].m_Tangent = glm::normalize(vertices[i].m_Tangent);
	}
}


#endif //TANGENTSPACE_H
