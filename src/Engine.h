#ifndef ENGINE_H
#define ENGINE_H

#include <cmath>

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

#include "Window.h"
#include "Camera.h"
#include "Shader.h"

#include "GraphicalObject.h"



struct Vertex
{
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	glm::vec3 m_Color;
	glm::vec2 m_TexCoords;
};


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

		//indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDrawElements(GL_TRIANGLES, m_ElementNumber, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

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
	glm::vec3 centerOffset;

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
			centerOffset(offset)
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
		glm::mat4 model = glm::translate(centerOffset);
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
		glm::mat4 model = glm::translate(centerOffset);
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
		model = glm::translate(centerOffset);
	}


};


class CubemapTexture
{
	std::string  m_Filenames[6];
	GLuint m_TextureObj;


public:
	CubemapTexture(std::string const& PosXFilename,
				   std::string const& NegXFilename,
				   std::string const& PosYFilename,
				   std::string const& NegYFilename,
				   std::string const& PosZFilename,
				   std::string const& NegZFilename)
	{
		m_Filenames[0] = PosXFilename;
		m_Filenames[1] = NegXFilename;
		m_Filenames[2] = PosYFilename;
		m_Filenames[3] = NegYFilename;
		m_Filenames[4] = PosZFilename;
		m_Filenames[5] = NegZFilename;
	}


	bool Load()
	{
		glGenTextures(1, &m_TextureObj);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureObj);

		//glActiveTexture(GL_TEXTURE0); // ?? in Bind method

		FIBITMAP* bitmap = nullptr;
		int width, height;

		GLenum types[6] =
				{
						GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				};

		for(GLuint i = 0; i < 6; ++i)
		{
			bitmap = FreeImage_Load(FreeImage_GetFileType(m_Filenames[i].c_str()), m_Filenames[i].c_str());
			width = FreeImage_GetWidth(bitmap);
			height = FreeImage_GetHeight(bitmap);


			FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
			FreeImage_FlipVertical(pImage); // KEK

			glTexImage2D(types[i], 0, GL_RGBA, width, height,
						 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

			FreeImage_Unload(bitmap);

		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return true;
	}

	void Bind(GLenum textureUnit)
	{
		glActiveTexture(textureUnit); // GL_TEXTURE 0
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureObj);
	}

	~CubemapTexture()
	{
		glDeleteTextures(1, &m_TextureObj);
	}

};


class Skybox: public GraphicalObject
{
	CubemapTexture m_CubemapTex;

	static const Vertex skyboxVertices[];
	static const GLuint skyboxIndices[];
	static const glm::vec3 offset;

public:
	Skybox(std::string const& PosXFilename,
		   std::string const& NegXFilename,
		   std::string const& PosYFilename,
		   std::string const& NegYFilename,
		   std::string const& PosZFilename,
		   std::string const& NegZFilename):
			GraphicalObject(skyboxVertices, 8, skyboxIndices, 36, offset),
			m_CubemapTex(PosXFilename,NegXFilename, PosYFilename, NegYFilename, PosZFilename, NegZFilename)
	{
		m_CubemapTex.Load();
	}

	void Draw(OrbitalCamera const& camera)
	{
		m_CubemapTex.Bind(GL_TEXTURE0);

		GLint OldCullFaceMode;
		glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
		GLint OldDepthFuncMode;
		glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

//		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);

		glDepthMask(GL_FALSE);

		GraphicalObject::Draw(camera);

		glCullFace((GLenum)OldCullFaceMode);
		glDepthFunc((GLenum)OldDepthFuncMode);

	//	glDisable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);

	}


};


class ShadowMapFBO
{
	GLuint m_FBO;
	GLuint m_ShadowMap;

public:

	ShadowMapFBO()
	{
		m_FBO = 0;
		m_ShadowMap = 0;
	}

	~ShadowMapFBO()
	{
		if(m_FBO != 0)
		{
			glDeleteFramebuffers(1, &m_FBO);
		}
		if (m_ShadowMap != 0){
			glDeleteFramebuffers(1, &m_ShadowMap);
		}
	}

	bool Init(int width, int height)
	{
		// Создаем FBO
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);


		// Создаем буфер глубины
		glGenTextures(1, &m_ShadowMap);
		glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_ShadowMap, 0);

		// Отключаем запись в буфер цвета
		glDrawBuffer(GL_NONE);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE){
			printf("FB error, status: 0x%x\n", Status);
			return false;
		}

		return true;
	}


	void BindForWriting()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
	}

	void BindForReading(GLenum TextureUnit)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glActiveTexture(TextureUnit);
		glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
	}
};

class ShadowMapTechnique
{
public:
	GLint m_TextureLocation;

	GLint m_LightBiasMVPID;

	ShadowMapFBO* m_pShadowMapFBO;


public:
	ShadowMapTechnique(ShadowMapFBO* pShadowMap)
	{
		m_TextureLocation = -1;
		m_LightBiasMVPID = -1;
		m_pShadowMapFBO = pShadowMap;
	}
	void Init(Shader const& shader)
	{
		m_TextureLocation = glGetUniformLocation(shader.Program(),"gShadowMap");
		m_LightBiasMVPID = glGetUniformLocation(shader.Program(), "lightBiasMVP");
	}

	void LoadLightBiasMVP(Shader const& shader, ShadowCamera const& camera, GraphicalObject const& object) const
	{
		shader.UseProgram();
		glm::mat4 mvp, model;
		object.GetModelMatrix(model);
		camera.GetMVP(mvp, model);
		glm::mat4 biasMatrix(
				0.5, 0.0, 0.0, 0.0,
				0.0, 0.5, 0.0, 0.0,
				0.0, 0.0, 0.5, 0.0,
				0.5, 0.5, 0.5, 1.0
		);
		//glm::mat4 lightBiasMVP = glm::translate( 0.5f * mvp, glm::vec3(0.5f, 0.5f, 0.5f));
		glm::mat4 lightBiasMVP =  biasMatrix * mvp;
		glUniformMatrix4fv(m_LightBiasMVPID, 1, GL_FALSE, &lightBiasMVP[0][0]);
		glUseProgram(0);

	}

	void WriteShadowTexture()
	{
		m_pShadowMapFBO->BindForWriting();
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void ReadShadowTexture(GLint textureUnit)
	{
		SetTextureUnit(textureUnit);
		m_pShadowMapFBO->BindForReading(GL_TEXTURE0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}


	void SetTextureUnit(GLint textureUnit)
	{
		glUniform1i(m_TextureLocation, textureUnit);
	}
};



#endif //ENGINE_H
