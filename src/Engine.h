#ifndef ENGINE_H
#define ENGINE_H

#include <cmath>


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>


#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <freeimage.h>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"


#define F_PI (float)M_PI


struct Point
{
	double x, y;
};

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

class Camera
{

protected:
	int m_Width;
	int m_Height;

	glm::mat4 m_Projection;
	glm::mat4 m_View;

public:

	glm::vec3 const CameraPosition = {0.0, 3.5, 4.5};
	glm::vec3 const Up = {0.0f, 1.0f, 0.0f};
	glm::vec3 const LookAt;

	Camera(int width = 500, int height = 500, glm::vec3 const& position = {}, glm::vec3 const& lookAt = {}):
			m_Width(width), m_Height(height), CameraPosition(position), LookAt(lookAt)
	{
		m_Projection = glm::perspectiveFovRH(glm::radians(45.0f), float(width), float(height), 0.1f, 100.0f);
		m_View = glm::lookAtRH(CameraPosition, LookAt, Up);
	}


	virtual void Update(Window& window)
	{

		int currentWidth, currentHeight;
		glfwGetFramebufferSize(window.GetGLFWPtr(), &currentWidth, &currentHeight);
		if((currentHeight != m_Height) || (currentWidth != m_Width))
		{
			m_Width = currentWidth;
			m_Height = currentHeight;

			m_Projection = glm::perspectiveFovRH(glm::radians(45.0f), float(m_Width), float(m_Height), 0.1f, 100.0f);

			glViewport ( 0, 0, (GLsizei)m_Width, (GLsizei)m_Height );
		}

	}

	void GetMVP(glm::mat4 &mvp, glm::mat4 const &model) const
	{
		mvp = m_Projection * m_View * model;
	}


	void GetView(glm::mat4 &view) const
	{
		view = m_View;
	}

};



class ShadowCamera: public Camera
{

public:
	ShadowCamera(int width = 500, int height = 500, glm::vec3 position = {}, glm::vec3 lookAt = {}):
			Camera(width, height, position, lookAt)
	{
		//m_Projection = glm::perspectiveFovRH(glm::radians(90.0f), float(m_Width), float(m_Height), 0.1f, 100.0f);
		m_Projection =  glm::ortho<float>(-10,10,-10,10,-10,20);
		m_View = glm::lookAtRH(position, LookAt, Up);
	}

	void Update(Window& window)
	{
		int currentWidth, currentHeight;
		glfwGetFramebufferSize(window.GetGLFWPtr(), &currentWidth, &currentHeight);
		if((currentHeight != m_Height) || (currentWidth != m_Width))
		{
			m_Width = currentWidth;
			m_Height = currentHeight;

			//m_Projection = glm::perspectiveFovRH(glm::radians(90.0f), float(m_Width), float(m_Height), 0.1f, 100.0f);

			m_Projection =  glm::ortho<float>(-10,10,-10,10,-10,20);

			glViewport ( 0, 0, (GLsizei)m_Width, (GLsizei)m_Height );
		}
	}

};

class OrbitalCamera: public Camera
{

private:

	float m_CameraRotationYaw = 0.0f;
	float m_CameraRotationPitch = 0.0f;
	Point m_PreviousCursorPosition = {};

	glm::vec3 m_DeltaOffset = {};

public:

	glm::vec3 const RotationCenter = {0.0f,0.0f,0.0f};
	glm::vec3 const Up = {0.0f, 1.0f, 0.0f};
	glm::vec3 const CenterOffset = {0.0f, 3.5f, 4.5f};
	//CameraPosition = translate(RotationCenter, CenterOffset); !

	OrbitalCamera(int width = 500, int height = 500):
			Camera(width, height)
	{
		m_Projection = glm::perspectiveFovRH(glm::radians(45.0f), float(width), float(height), 0.1f, 100.0f);
		m_View = glm::lookAtRH(glm::vec3(glm::translate(RotationCenter) * glm::vec4(CenterOffset, 1.0f)),
							   RotationCenter, Up);
	}


	void Update(Window window)
	{
		Camera::Update(window);
		if(glfwGetMouseButton(window.GetGLFWPtr(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			Point currentCursorPosition;
			glfwGetCursorPos(window.GetGLFWPtr(), &currentCursorPosition.x, &currentCursorPosition.y);

			auto const deltaPitch = static_cast<float>(currentCursorPosition.y - m_PreviousCursorPosition.y) / m_Height;
			auto const deltaYaw = static_cast<float>(currentCursorPosition.x - m_PreviousCursorPosition.x) / m_Width;

			m_CameraRotationYaw -= deltaYaw;
			m_CameraRotationPitch = glm::clamp(m_CameraRotationPitch - deltaPitch, -F_PI/2.0f, F_PI / 2.0f);

			auto const translation = glm::translate(RotationCenter);
			auto const cameraRotation = glm::yawPitchRoll(m_CameraRotationYaw, m_CameraRotationPitch, 0.0f);


			m_View = glm::lookAtRH(glm::vec3(translation * cameraRotation * glm::vec4(CenterOffset + m_DeltaOffset, 1.0f)),
								   RotationCenter, glm::vec3(cameraRotation * glm::vec4(Up, 1.0f)));



		}
		auto const wState = glfwGetKey(window.GetGLFWPtr(), GLFW_KEY_W);
		auto const sState = glfwGetKey(window.GetGLFWPtr(), GLFW_KEY_S);

		if(wState == GLFW_PRESS)
		{
			m_DeltaOffset -= 0.01f*CenterOffset;
			auto const translation = glm::translate(RotationCenter);
			auto const cameraRotation = glm::yawPitchRoll(m_CameraRotationYaw, m_CameraRotationPitch, 0.0f);


			m_View = glm::lookAtRH(glm::vec3(translation * cameraRotation * glm::vec4(CenterOffset + m_DeltaOffset, 1.0f)),
								   RotationCenter, glm::vec3(cameraRotation* glm::vec4(Up, 1.0f)));
		}
		if(sState == GLFW_PRESS)
		{
			m_DeltaOffset += 0.01f*CenterOffset;
			auto const translation = glm::translate(RotationCenter);
			auto const cameraRotation = glm::yawPitchRoll(m_CameraRotationYaw, m_CameraRotationPitch, 0.0f);


			m_View = glm::lookAtRH(glm::vec3(translation * cameraRotation * glm::vec4(CenterOffset + m_DeltaOffset, 1.0f)),
								   RotationCenter, glm::vec3(cameraRotation* glm::vec4(Up, 1.0f)));
		}

		glfwGetCursorPos(window.GetGLFWPtr(), &m_PreviousCursorPosition.x, &m_PreviousCursorPosition.y);
	}


};


class GraphicalObject
{
	Mesh m_Mesh;
	glm::vec3 centerOffset;

	Shader* m_pShader;


	GLint mvpID;
	GLint modelID;
	GLint normalMatID;

	GLint viewID;

	GLint lightPositionID;



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

		lightPositionID = glGetUniformLocation(shader.Program(), "lightPosition");

		m_pShader = &shader;
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

	void DrawIlluminated(Camera const& camera, glm::vec4 const& lightPosition)
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

		glUniform4fv(lightPositionID, 1, &lightPosition[0]);

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

	void LoadLightBiasMVP(ShadowCamera const& camera, GraphicalObject const& object) const
	{
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
