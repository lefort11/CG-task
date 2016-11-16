#ifndef LIGHTNINGTECHNIQUE_H
#define LIGHTNINGTECHNIQUE_H

#include "Shader.h"
#include "Texture.h"

#define SHADOW_TEXTURE_UNIT GL_TEXTURE0
#define COLOR_TEXTURE_UNIT GL_TEXTURE1
#define NORMAL_TEXTURE_UNIT GL_TEXTURE2
#define SKYBOX_TEXTURE_UNIT GL_TEXTURE3
#define HEIGHT_TEXTURE_UNIT GL_TEXTURE4


class LightningTechnique
{
public:

	LightningTechnique() {}

	LightningTechnique(LightningTechnique const& other) {}

	virtual void Init(Shader const& shader) = 0;

	virtual void DoStuff(Shader const& shader, glm::mat4 const& model) const = 0;

	virtual LightningTechnique* Clone() = 0;

//	virtual void DoStuff(Shader const& shader) = 0;


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

	ShadowMapFBO(ShadowMapFBO const& other)
	{
		m_FBO = other.m_FBO;
		m_ShadowMap = other.m_ShadowMap;
	}

	~ShadowMapFBO()
	{
		if(m_FBO != 0)
		{
			glDeleteFramebuffers(1, &m_FBO);
		}
		if (m_ShadowMap != 0)
		{
			glDeleteTextures(1, &m_ShadowMap);
		}
	}

	bool Init(int width, int height)
	{
		// Создаем FBO
		glGenFramebuffers(1, &m_FBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO);

//		glViewport(0, 0, width, height);


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

	ShadowCamera* m_pShadowCamera;


public:
	ShadowMapTechnique(ShadowMapFBO* pShadowMap, ShadowCamera* pShadowCamera)
	{
		m_TextureLocation = -1;
		m_LightBiasMVPID = -1;
		m_pShadowMapFBO = pShadowMap;
		m_pShadowCamera = pShadowCamera;
	}

/*	ShadowMapTechnique(ShadowMapTechnique const& other)
	{
		m_TextureLocation = other.m_TextureLocation;
		m_LightBiasMVPID = other.m_LightBiasMVPID;
		m_pShadowCamera = new ShadowCamera(*(other.m_pShadowCamera));
		m_pShadowMapFBO = new ShadowMapFBO(*(other.m_pShadowMapFBO));

	} */
	void Init(Shader const& shader)
	{
		m_TextureLocation = glGetUniformLocation(shader.Program(),"shadowMap");
		m_LightBiasMVPID = glGetUniformLocation(shader.Program(), "lightBiasMVP");
	}

	void LoadLightBiasMVP(Shader const& shader, glm::mat4 model) const
	{
		shader.UseProgram();
		glm::mat4 mvp;
		m_pShadowCamera->GetMVP(mvp, model);
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

	void ReadShadowTexture(GLenum textureUnit, Shader const& shader) const // binds Texture to sampler
	{
		shader.UseProgram();
		SetTextureUnit(textureUnit - GL_TEXTURE0);
		m_pShadowMapFBO->BindForReading(textureUnit);
	}

	void SetTextureUnit(GLint textureUnit) const
	{
		glUniform1i(m_TextureLocation, textureUnit);
	}

	void DoStuff(Shader const& shader, glm::mat4 const& model) const
	{
		LoadLightBiasMVP(shader, model);
		ReadShadowTexture(SHADOW_TEXTURE_UNIT, shader);
	}

	LightningTechnique* Clone()
	{
		return new ShadowMapTechnique(*this);
	}


};

class NormalMapTechnique: public LightningTechnique
{
	GLint m_NormalMapLocation;
	GLint m_ColorMapLocation;

	Texture* m_pNormalTex;
	Texture* m_pColorTex;

public:

	NormalMapTechnique(Texture& normalTexture, Texture& colorTexture): m_NormalMapLocation(-1),
																	   m_ColorMapLocation(-1),
																	   m_pNormalTex(&normalTexture),
																	   m_pColorTex(&colorTexture)
	{
		m_pNormalTex->Load();
		m_pColorTex->Load();
	}

	virtual void Init(Shader const& shader)
	{
		m_NormalMapLocation = glGetUniformLocation(shader.Program(), "normalMap");
		m_ColorMapLocation = glGetUniformLocation(shader.Program(), "colorMap");
	}

	virtual void LoadTextures(Texture& normalTexture, Texture& colorTexture)
	{
		m_pNormalTex = &normalTexture;
		m_pColorTex = &colorTexture;
		m_pNormalTex->Load();
		m_pColorTex->Load();
	}

	virtual void BindTextures(Shader const& shader) const
	{
		shader.UseProgram();
		m_pNormalTex->Bind(NORMAL_TEXTURE_UNIT);
		glUniform1i(m_NormalMapLocation, NORMAL_TEXTURE_UNIT - GL_TEXTURE0);
		m_pColorTex->Bind(COLOR_TEXTURE_UNIT);
		glUniform1i(m_ColorMapLocation, COLOR_TEXTURE_UNIT - GL_TEXTURE0);
	}

	virtual void DoStuff(Shader const& shader, glm::mat4 const& model) const
	{
		BindTextures(shader);
	}

	virtual LightningTechnique* Clone()
	{
		return new NormalMapTechnique(*this);
	}
};

class ParallaxTechnique: public NormalMapTechnique
{
	GLint m_HeightMapLocation;

	Texture* m_pHeightTexture;

public:
	ParallaxTechnique(Texture& normalTexture, Texture& colorTexture, Texture& heightTexture):
			NormalMapTechnique(normalTexture, colorTexture), m_pHeightTexture(&heightTexture)
	{
		m_pHeightTexture->Load();
	}

	void Init(Shader const& shader)
	{
		NormalMapTechnique::Init(shader);
		m_HeightMapLocation = glGetUniformLocation(shader.Program(), "heightMap");
	}

	void BindTextures(Shader const& shader) const
	{
		NormalMapTechnique::BindTextures(shader);
		m_pHeightTexture->Bind(HEIGHT_TEXTURE_UNIT);
		glUniform1i(m_HeightMapLocation, HEIGHT_TEXTURE_UNIT - GL_TEXTURE0);
	}

	virtual void DoStuff(Shader const& shader, glm::mat4 const& model) const
	{
		BindTextures(shader);
	}

	virtual LightningTechnique* Clone()
	{
		return new ParallaxTechnique(*this);
	}


};

#endif //LIGHTNINGTECHNIQUE_H
