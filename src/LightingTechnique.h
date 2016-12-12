#ifndef LIGHTNINGTECHNIQUE_H
#define LIGHTNINGTECHNIQUE_H

#include "Shader.h"
#include "Texture.h"
#include "FBO.h"

#define SHADOW_TEXTURE_UNIT GL_TEXTURE0
#define COLOR_TEXTURE_UNIT GL_TEXTURE1
#define NORMAL_TEXTURE_UNIT GL_TEXTURE2
#define SKYBOX_TEXTURE_UNIT GL_TEXTURE3
#define HEIGHT_TEXTURE_UNIT GL_TEXTURE4
#define POSITION_TEXTURE_UNIT GL_TEXTURE5
#define INPUT_TEXTURE_UNIT GL_TEXTURE6
#define AO_TEXTURE_UNIT GL_TEXTURE7

class LightingTechnique
{
public:

	LightingTechnique() {}

	LightingTechnique(LightingTechnique const& other) {}

	virtual void Init(Shader const& shader) = 0;

	virtual void DoStuff(Shader const& shader, glm::mat4 const& model) const = 0;

	virtual LightingTechnique* Clone() = 0;


};


class ShadowMapFBO: public FBO
{
public:

	void Init(int width, int height)
	{
		FBO::Init(width, height, true, GL_NONE);
	}

};


class ShadowMapTechnique: public LightingTechnique
{

	GLint m_TextureID;

	GLint m_LightBiasMVPID;

	ShadowMapFBO* m_pShadowMapFBO;

	ShadowCamera* m_pShadowCamera;


public:
	ShadowMapTechnique(ShadowMapFBO* pShadowMap, ShadowCamera* pShadowCamera)
	{
		m_TextureID = -1;
		m_LightBiasMVPID = -1;
		m_pShadowMapFBO = pShadowMap;
		m_pShadowCamera = pShadowCamera;
	}

/*	ShadowMapTechnique(ShadowMapTechnique const& other)
	{
		m_TextureID = other.m_TextureID;
		m_LightBiasMVPID = other.m_LightBiasMVPID;
		m_pShadowCamera = new ShadowCamera(*(other.m_pShadowCamera));
		m_pShadowMapFBO = new ShadowMapFBO(*(other.m_pShadowMapFBO));

	} */
	void Init(Shader const& shader)
	{
		m_TextureID = glGetUniformLocation(shader.Program(),"shadowMap");
		m_LightBiasMVPID = glGetUniformLocation(shader.Program(), "lightBiasMVP");

	}

	void LoadLightBiasMVP(Shader const& shader, glm::mat4 const& model) const
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

	void WriteShadowTexture() const
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
		glUniform1i(m_TextureID, textureUnit);
	}

	void DoStuff(Shader const& shader, glm::mat4 const& model) const
	{
		LoadLightBiasMVP(shader, model);
		ReadShadowTexture(SHADOW_TEXTURE_UNIT, shader);

	}

	void ShadowMapPassInit() const
	{
		glCullFace(GL_FRONT);
		WriteShadowTexture();
	}

	void RenderPassInit() const
	{
		glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	LightingTechnique* Clone()
	{
		return new ShadowMapTechnique(*this);
	}


};

class NormalMapTechnique: public LightingTechnique
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

	virtual LightingTechnique* Clone()
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

	virtual LightingTechnique* Clone()
	{
		return new ParallaxTechnique(*this);
	}


};

#endif //LIGHTNINGTECHNIQUE_H
