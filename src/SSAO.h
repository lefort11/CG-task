#ifndef SSAO_H
#define SSAO_H

#include "FBO.h"
#include "Shader.h"
#include "LightingTechnique.h"
#include "Camera.h"
#include "Vertex.h"
#include "GraphicalObject.h"


class SSAOTechnique
{
	FBO* m_gBuffer;
	FBO* m_aoBuffer;
	FBO* m_blurBuffer;

	Shader* m_pGeomPassShader;
	Shader* m_pAOPassShader;
	Shader* m_pBlurPassShader;
	Shader* m_pLightningPassShader;

	GraphicalObject quad;

	Camera* m_pCamera;

public:
	static Vertex quadVertices[];
	static GLuint quadIndices[];


public:

	SSAOTechnique(FBO& gBuffer, FBO& aoBuffer, FBO& blurBuffer): m_gBuffer(&gBuffer),
																 m_aoBuffer(&aoBuffer),
																 m_blurBuffer(&blurBuffer),
																 m_pGeomPassShader(nullptr),
																 m_pAOPassShader(nullptr),
																 m_pBlurPassShader(nullptr),
																 m_pLightningPassShader(nullptr),
																 quad(quadVertices, 4, quadIndices, 6),
																 m_pCamera(nullptr)
	{}
	void Init(Shader& geomPassShader, Shader& aoPassShader, Shader& blurPassShader, Shader& lightningPassShader,
			  Camera& camera, int width, int height)
	{
		m_pGeomPassShader = &geomPassShader;
		m_pAOPassShader = &aoPassShader;
		m_pBlurPassShader = &blurPassShader;
		m_pLightningPassShader = &lightningPassShader;
		m_pCamera = &camera;

		GLint posTextureUnitLocation = glGetUniformLocation(aoPassShader.Program(), "gPositionMap");
		GLint projmatLocation = glGetUniformLocation(aoPassShader.Program(), "proj");
		GLint kernelLocation = glGetUniformLocation(aoPassShader.Program(), "gKernel");


		GLint inputTextureUnitLocation = glGetUniformLocation(blurPassShader.Program(), "gColorMap");
		GLint aoTextureUnitLocation = glGetUniformLocation(lightningPassShader.Program(), "gAOMap");
		GLint screenSizeLocation = glGetUniformLocation(lightningPassShader.Program(), "ScreenSize");

		blurPassShader.UseProgram();
		glUniform1i(inputTextureUnitLocation, INPUT_TEXTURE_UNIT - GL_TEXTURE0);

		lightningPassShader.UseProgram();
		glUniform1i(aoTextureUnitLocation, AO_TEXTURE_UNIT - GL_TEXTURE0);
		glUniform2f(screenSizeLocation, width, height);

		int const KERNEL_SIZE = 32;

		glm::vec3 kernel[KERNEL_SIZE];

		for(int i = 0; i < KERNEL_SIZE; ++i)
		{
			float scale = (float)i / (float)(KERNEL_SIZE);
			glm::vec3 v;
			v.x = 2.0f * (float)rand()/RAND_MAX - 1.0f;
			v.y = 2.0f * (float)rand()/RAND_MAX - 1.0f;
			v.z = 2.0f * (float)rand()/RAND_MAX - 1.0f;
			// Use an acceleration function so more points are
			// located closer to the origin
			v *= (0.1f + 0.9f * scale * scale);

			kernel[i] = v;
		}

		aoPassShader.UseProgram();
		glUniform3fv(kernelLocation, KERNEL_SIZE, (GLfloat const*) &kernel[0]);
		glUniform1i(posTextureUnitLocation, POSITION_TEXTURE_UNIT - GL_TEXTURE0);
		glm::mat4 proj;
		camera.GetProjection(proj);
		glUniformMatrix4fv(projmatLocation, 1, GL_FALSE, &proj[0][0]);



	}
	void GeometryPassInit()
	{
		m_gBuffer->BindForWriting();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}
	void SSAOPass()
	{
		m_pAOPassShader->UseProgram();

		m_gBuffer->BindForReading(POSITION_TEXTURE_UNIT);
		m_aoBuffer->BindForWriting();
		glClear(GL_COLOR_BUFFER_BIT);
		quad.LoadShader(*m_pAOPassShader);
		quad.Draw(*m_pCamera);
	}
	void BlurPass()
	{
		m_aoBuffer->BindForReading(INPUT_TEXTURE_UNIT);
		m_blurBuffer->BindForWriting();
		glClear(GL_COLOR_BUFFER_BIT);
		quad.LoadShader(*m_pBlurPassShader);
		quad.Draw(*m_pCamera);
	}
	void LightningPassInit()
	{
		m_blurBuffer->BindForReading(AO_TEXTURE_UNIT);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};


#endif //SSAO_H
