#ifndef REFLECTIONTECHNIQUE_H
#define REFLECTIONTECHNIQUE_H

#include "LightningTechnique.h"
#include "Camera.h"

class ReflectionFBO
{
	GLuint m_FBO;
	GLuint m_ReflectionMap;
	GLuint m_DepthBuffer;

public:

	ReflectionFBO()
	{
		m_FBO = 0;
		m_ReflectionMap = 0;
		m_DepthBuffer = 0;
	}

	ReflectionFBO(ReflectionFBO const &other)
	{
		m_FBO = other.m_FBO;
		m_ReflectionMap = other.m_ReflectionMap;
		m_DepthBuffer = other.m_DepthBuffer;
	}

	~ShadowMapFBO()
	{
		if (m_FBO != 0)
		{
			glDeleteFramebuffers(1, &m_FBO);
		}
		if (m_ReflectionMap != 0)
		{
			glDeleteTextures(1, &m_ReflectionMap);
		}
		if (m_DepthBuffer != 0)
		{
			glDeleteTextures(1, &m_DepthBuffer);
		}
	}

	bool Init(int width, int height)
	{
		// Creating FBO
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);

		glViewport(0, 0, width, height);


		// Creating color buffer
		glGenTextures(1, &m_ReflectionMap);
		glBindTexture(GL_TEXTURE_2D, m_ReflectionMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

		// Creating depth buffer
		glGenRenderbuffers(1, &m_DepthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);


		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ReflectionMap, 0);


		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glDrawBuffer(GL_DEPTH_ATTACHMENT);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE)
		{
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
		glBindTexture(GL_TEXTURE_2D, m_ReflectionMap);
	}
};

class MirrorCamera: public OrbitalCamera
{
public:

	void Update(OrbitalCamera const& camera)
	{


	}

};


class ReflectionTechnique: public LightningTechnique
{
	ReflectionFBO* m_pReflectionFBO;

//	MirrorCamera* m_pMirrorCamera;

	GLint m_TextureLocation;

public:

	ReflectionTechnique(ReflectionFBO* pReflectionFBO, MirrorCamera* pMirrorCamera): m_pReflectionFBO(pReflectionFBO),
																					 //m_pMirrorCamera(pMirrorCamera),
																					 m_TextureLocation(-1)
	{}

	void Init(Shader const& shader)
	{
		m_TextureLocation = glGetUniformLocation(shader.Program(),"reflectionMap");
	}

	void WriteReflectionTexture()
	{
		m_pReflectionFBO->BindForWriting();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void LoadCameraMVP()
	{

	}


	void ReadReflectionTexture(GLenum textureUnit, Shader const& shader) const
	{
		shader.UseProgram();
		glUniform1i(m_TextureLocation, textureUnit - GL_TEXTURE0);
		m_pReflectionFBO->BindForReading(textureUnit);
	}

	void DoStuff(Shader const& shader, glm::mat4 const& model) const
	{
		ReadReflectionTexture(SHADOW_TEXTURE_UNIT, shader);
	}

	LightningTechnique* Clone()
	{
		return new ReflectionTechnique(*this);
	}


};

#endif //REFLECTIONTECHNIQUE_H
