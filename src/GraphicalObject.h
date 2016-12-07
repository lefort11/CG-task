#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <freeimage.h>

#include "Vertex.h"
#include "Shader.h"
#include "Camera.h"
#include "LightingTechnique.h"

class Mesh
{

	GLuint m_VertexBuffer;
	GLuint m_ElementBuffer;

	GLuint m_VertexArray; //VAO

	unsigned  m_VertexNumber;
	unsigned m_ElementNumber;

public:
	Mesh(Vertex const* vertices, unsigned const verticesNumber,
		 GLuint const* indices, unsigned const indicesNumber): m_ElementNumber(indicesNumber),
															   m_VertexNumber(verticesNumber)
	{
		//Setting up VAO
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		//Setting up vertices buffer
		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, verticesNumber * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		//Setting up indices
		glGenBuffers(1, &m_ElementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesNumber * sizeof(GLuint), indices, GL_STATIC_DRAW);


		glBindVertexArray(0);

	}

	~Mesh()
	{
		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteBuffers(1, &m_ElementBuffer);
	}



	void Draw() const
	{

		glBindVertexArray(m_VertexArray); //VAO

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		//Vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		//Vertex normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_Normal));

		//Vertex color
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_Color));

		//Tex coords
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_TexCoords));

		//tangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_Tangent));

		//Bitangent
//		glEnableVertexAttribArray(5);
//		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_Bitangent));

		//indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDrawElements(GL_TRIANGLES, m_ElementNumber, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
//		glDisableVertexAttribArray(5);

		glBindVertexArray(0);

	}

};

struct Material
{
	glm::vec4 Specular;
	glm::vec4 Ambient;
	glm::vec4 Diffuse;
	float Shininess;

	std::vector<LightingTechnique*> m_LightningTechniques;

public:

	Material(glm::vec4 specular = glm::vec4(0.9,0.9,0.9,1.0),
			 glm::vec4 ambient = glm::vec4(0.2,0.2,0.2,1.0),
			 glm::vec4 diffuse = glm::vec4(0.7,0.7,0.7,1.0),
			 float shininess  = 0.0):
			Specular(specular),
			Ambient(ambient),
			Diffuse(diffuse),
			Shininess(shininess)
	{}


	void LoadLightningTechniques(std::vector<LightingTechnique*> lightningTechniques)
	{
		m_LightningTechniques = lightningTechniques;
	}

	void AddLightningTechnique(LightingTechnique& lightningTechnique)
	{
		m_LightningTechniques.push_back(lightningTechnique.Clone());
	}

	void InitLightningTechniques(Shader const& shader)
	{
		for(int i = 0; i < m_LightningTechniques.size(); ++i)
		{
			m_LightningTechniques[i]->Init(shader);
		}
	}

	void DoStuff(Shader const& shader, glm::mat4 const& model)
	{
		for(int i = 0; i < m_LightningTechniques.size(); ++i)
		{
			m_LightningTechniques[i]->DoStuff(shader, model);
		}
	}



};



class GraphicalObject
{
	Mesh m_Mesh;
	glm::vec3 m_CenterOffset;
	glm::vec3 m_Rotatation;
	glm::vec3 m_Scale;

	Shader* m_pShader;

	Material* m_pMaterial;



public:
	GraphicalObject(Vertex const* vertices, unsigned const verticesNumber, GLuint const* indices,
					unsigned const indicesNumber, glm::vec3 const& offset = {}, glm::vec3 const& rotate = glm::vec3(0.0f),
					glm::vec3 scale = glm::vec3(1.0f)):
			m_Mesh(vertices,  verticesNumber, indices, indicesNumber),
			m_CenterOffset(offset), m_Rotatation(rotate), m_Scale(scale)
	{}


	void Rotate(glm::vec3 rotation)
	{
		m_Rotatation = rotation;
	}


	~GraphicalObject()
	{

	}

	void LoadShader(Shader& shader)
	{
		m_pShader = &shader;
	}

	void LoadMaterial(Material& material)
	{
		m_pMaterial = &material;
		m_pMaterial->InitLightningTechniques(*m_pShader);

	}


	void Draw(Camera const& camera) const
	{
		m_pShader->UseProgram();

		glm::mat4 mvp;
		glm::mat4 model = glm::translate(m_CenterOffset) * glm::toMat4(glm::quat(m_Rotatation)) * glm::scale(m_Scale);
		camera.GetMVP(mvp, model);


		glm::mat4 view;
		camera.GetView(view);

		glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3x3(model)));

		glUniformMatrix4fv(m_pShader->MVPID(), 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(m_pShader->ModelID(), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(m_pShader->NormalMatID(), 1, GL_FALSE, &normalMat[0][0]);

		glUniformMatrix4fv(m_pShader->ViewID(), 1, GL_FALSE, &view[0][0]);

		m_Mesh.Draw();

		glUseProgram(0);

	}

	void DrawIlluminated(Camera const& camera, glm::vec4 const& lightDirection)
	{
		m_pShader->UseProgram();

		glm::mat4 mvp;
		glm::mat4 model = glm::translate(m_CenterOffset) * glm::toMat4(glm::quat(m_Rotatation)) * glm::scale(m_Scale);
		camera.GetMVP(mvp, model);

		glm::mat4 view;
		camera.GetView(view);

		glm::mat4 lightViewMat = glm::lookAt(-glm::vec3(lightDirection), glm::vec3(0.0f, 0.0f, 0.0f),
											 {0.0f, 1.0f, 0.0f});

//		glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3x3(lightViewMat * model)));

		glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3x3(view * model)));

		glUniformMatrix4fv(m_pShader->MVPID(), 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(m_pShader->ModelID(), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(m_pShader->NormalMatID(), 1, GL_FALSE, &normalMat[0][0]);

		glUniformMatrix4fv(m_pShader->ViewID(), 1, GL_FALSE, &view[0][0]);

		glUniform4fv(m_pShader->LightDirectionID(), 1, &lightDirection[0]);

		glUniform4fv(m_pShader->MaterialSpecularID(), 1, &(m_pMaterial->Specular[0]));
		glUniform4fv(m_pShader->MaterialDiffuseID(), 1, &(m_pMaterial->Diffuse[0]));
		glUniform4fv(m_pShader->MaterialAmbientID(), 1, &(m_pMaterial->Ambient[0]));
		glUniform1f(m_pShader->MaterialShininessID(), m_pMaterial->Shininess);
		glUniformMatrix4fv(m_pShader->LightViewID(), 1, GL_FALSE, &lightViewMat[0][0]);

		m_pMaterial->DoStuff(*m_pShader, model);

		m_Mesh.Draw();

		glUseProgram(0);
	}


	void DeleteShader()
	{
		m_pShader->DeleteProgram();
	}

	void GetModelMatrix(glm::mat4& model) const
	{
		model = glm::translate(m_CenterOffset) * glm::toMat4(glm::quat(m_Rotatation)) * glm::scale(m_Scale);
	}


};

#endif //GRAPHICALOBJECT_H
