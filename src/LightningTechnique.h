#ifndef LIGHTNINGTECHNIQUE_H
#define LIGHTNINGTECHNIQUE_H

#include "Shader.h"
#include "GraphicalObject.h"


class LightningTechnique
{
public:
	virtual void Init(Shader const& shader) = 0;
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

		glViewport(0, 0, width, height);


		// Создаем буфер глубины
		glGenTextures(1, &m_ShadowMap);
		glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

/*		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE); */

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


class ShadowMapTechnique: public LightningTechnique
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
		m_TextureLocation = glGetUniformLocation(shader.Program(),"shadowMap");
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

	void ReadShadowTexture(GLenum textureUnit)
	{
		SetTextureUnit(textureUnit - GL_TEXTURE0);
		m_pShadowMapFBO->BindForReading(textureUnit);
	}


	void SetTextureUnit(GLint textureUnit)
	{
		glUniform1i(m_TextureLocation, textureUnit);
	}


};

#endif //LIGHTNINGTECHNIQUE_H
