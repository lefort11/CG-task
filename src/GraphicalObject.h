#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <freeimage.h>

#include "Vertex.h"
#include "Shader.h"
#include "Camera.h"

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


		//calculating tangents


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

		//indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDrawElements(GL_TRIANGLES, m_ElementNumber, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);

		glBindVertexArray(0);

	}

};

struct Material
{
	glm::vec4 Specular;
	glm::vec4 Ambient;
	glm::vec4 Diffuse;
	float Shininess;

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

};



class GraphicalObject
{
	Mesh m_Mesh;
	glm::vec3 m_CenterOffset;

	Shader* m_pShader;

	Material* m_pMaterial;

	GLint mvpID;
	GLint modelID;
	GLint normalMatID;

	GLint viewID;

	GLint lightDirectionID;


	GLint lightViewID;

	GLint MaterialSpecularID;
	GLint MaterialAmbientID;
	GLint MaterialDiffuseID;
	GLint MaterialShininessID;


public:
	GraphicalObject(Vertex const* vertices, unsigned const verticesNumber, GLuint const* indices,
					unsigned const indicesNumber, glm::vec3 const& offset):
			m_Mesh(vertices,  verticesNumber, indices, indicesNumber),
			m_CenterOffset(offset)
	{}

	~GraphicalObject()
	{
		DeleteShader();
	}

	void LoadShader(Shader& shader)
	{
		mvpID = glGetUniformLocation(shader.Program(), "mvp");
		modelID = glGetUniformLocation(shader.Program(), "model");
		normalMatID = glGetUniformLocation(shader.Program(), "normalMat");

		viewID = glGetUniformLocation(shader.Program(), "view");

		lightDirectionID = glGetUniformLocation(shader.Program(), "lightDirection");

		lightViewID = glGetUniformLocation(shader.Program(), "lightViewMat");




		m_pShader = &shader;
	}

	void LoadMaterial(Material& material)
	{
		m_pMaterial = &material;
		MaterialAmbientID = glGetUniformLocation(m_pShader->Program(), "MaterialAmbient");
		MaterialDiffuseID = glGetUniformLocation(m_pShader->Program(), "MaterialDiffuse");
		MaterialSpecularID = glGetUniformLocation(m_pShader->Program(), "MaterialSpecular");
		MaterialShininessID = glGetUniformLocation(m_pShader->Program(), "Shininess");
	}


	void Draw(Camera const& camera) const
	{
		m_pShader->UseProgram();

		glm::mat4 mvp;
		glm::mat4 model = glm::translate(m_CenterOffset);
		camera.GetMVP(mvp, model);

		glm::mat4 view;
		camera.GetView(view);

		glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3x3(model)));

		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(normalMatID, 1, GL_FALSE, &normalMat[0][0]);

		glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);


		m_Mesh.Draw();

		glUseProgram(0);

	}

	void DrawIlluminated(Camera const& camera, glm::vec4 const& lightDirection)
	{
		m_pShader->UseProgram();

		glm::mat4 mvp;
		glm::mat4 model = glm::translate(m_CenterOffset);
		camera.GetMVP(mvp, model);

		glm::mat4 view;
		camera.GetView(view);

		glm::mat4 lightViewMat = glm::lookAt(-glm::vec3(lightDirection), glm::vec3(0.0f, 0.0f, 0.0f),
											 {0.0f, 1.0f, 0.0f});

//		glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3x3(lightViewMat * model)));

		glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3x3(view * model)));

		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix3fv(normalMatID, 1, GL_FALSE, &normalMat[0][0]);

		glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);

		glUniform4fv(lightDirectionID, 1, &lightDirection[0]);

		glUniform4fv(MaterialSpecularID, 1, &(m_pMaterial->Specular[0]));
		glUniform4fv(MaterialDiffuseID, 1, &(m_pMaterial->Diffuse[0]));
		glUniform4fv(MaterialAmbientID, 1, &(m_pMaterial->Ambient[0]));
		glUniform1f(MaterialShininessID, m_pMaterial->Shininess);



		glUniformMatrix4fv(lightViewID, 1, GL_FALSE, &lightViewMat[0][0]);

		m_Mesh.Draw();

		glUseProgram(0);
	}


	void DeleteShader()
	{
		m_pShader->DeleteProgram();
	}

	void GetModelMatrix(glm::mat4& model) const
	{
		model = glm::translate(m_CenterOffset);
	}


};

#endif //GRAPHICALOBJECT_H
