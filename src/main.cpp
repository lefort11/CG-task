#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


#include "Window.h"
#include "Engine.h"

#define WIDTH 600
#define  HEIGHT 600


GLuint const planeIndices[] =
		{
				0, 3, 2,
				2, 1, 0
		};

Vertex const Skybox::skyboxVertices[] =
		{
				{200.0f * glm::vec3(-0.5f, -0.5f, -0.5f), {-1.0f, -1.0f, -1.0f}, {},{}},
				{200.0f * glm::vec3(-0.5f, 0.5f, -0.5f), {-1.0f, 1.0f, -1.0f}, {},{}},
				{200.0f * glm::vec3(0.5f, 0.5f, -0.5f), {1.0f, 1.0f, -1.0f}, {},{}},
				{200.0f*glm::vec3(0.5f, -0.5f, -0.5f), {1.0f, -1.0f, -1.0f}, {},{}},
				{200.0f*glm::vec3(-0.5f, -0.5f, 0.5f), {-1.0f, -1.0f, 1.0f}, {},{}},
				{200.0f*glm::vec3(-0.5f, 0.5f, 0.5f), {-1.0f, 1.0f, 1.0f}, {},{}},
				{200.0f*glm::vec3(0.5f, 0.5f, 0.5f), {1.0f, 1.0f, 1.0f}, {},{}},
				{200.0f*glm::vec3(0.5f, -0.5f, 0.5f), {1.0f, -1.0f, 1.0f}, {},{}}

		};


GLuint const Skybox::skyboxIndices[] =
		{
				// right
				3, 2, 6,
				6, 7, 3,
				// left
				4, 5, 1,
				1, 0, 4,
				// top
				1, 5, 6,
				6, 2, 1,
				// bottom
				4, 0, 3,
				3, 7, 4,

				// front
				0, 1, 2,
				2, 3, 0,
				// back
				7, 6, 5,
				5, 4, 7

		};

glm::vec3 const Skybox::offset = glm::vec3(0.0f, 0.0f, 0.0f);



Vertex cube_vertices[] =
		{
				{glm::vec3(-0.5f, -0.5f, -0.5f), {-1.0f, -1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{glm::vec3(-0.5f, 0.5f, -0.5f), {-1.0f, 1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{glm::vec3(0.5f, 0.5f, -0.5f), {1.0f, 1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{glm::vec3(0.5f, -0.5f, -0.5f), {1.0f, -1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{glm::vec3(-0.5f, -0.5f, 0.5f), {-1.0f, -1.0f, 1.0f}, {1.0f,0.0f,0.0f},{}},
				{glm::vec3(-0.5f, 0.5f, 0.5f), {-1.0f, 1.0f, 1.0f}, {1.0f,0.0f,0.0f},{}},
				{glm::vec3(0.5f, 0.5f, 0.5f), {1.0f, 1.0f, 1.0f}, {1.0f,0.0,0.0f},{}},
				{glm::vec3(0.5f, -0.5f, 0.5f), {1.0f, -1.0f, 1.0f}, {1.0f,0.0f,0.0f},{}}
		};

Vertex cube_vertices2[] =
		{
				{3.0f * glm::vec3(-0.5f, -0.5f, -0.5f), {-1.0f, -1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{3.0f * glm::vec3(-0.5f, 0.5f, -0.5f), {-1.0f, 1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{3.0f * glm::vec3(0.5f, 0.5f, -0.5f), {1.0f, 1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{3.0f * glm::vec3(0.5f, -0.5f, -0.5f), {1.0f, -1.0f, -1.0f}, {1.0f,0.0f,0.0f},{}},
				{3.0f * glm::vec3(-0.5f, -0.5f, 0.5f), {-1.0f, -1.0f, 1.0f}, {1.0f,0.0f,0.0f},{}},
				{3.0f * glm::vec3(-0.5f, 0.5f, 0.5f), {-1.0f, 1.0f, 1.0f}, {1.0f,0.0f,0.0f},{}},
				{3.0f * glm::vec3(0.5f, 0.5f, 0.5f), {1.0f, 1.0f, 1.0f}, {1.0f,0.0,0.0f},{}},
				{3.0f * glm::vec3(0.5f, -0.5f, 0.5f), {1.0f, -1.0f, 1.0f}, {1.0f,0.0f,0.0f},{}}
		};

GLuint cube_indices[] =
		{
				// back
				0, 1, 2,
				2, 3, 0,
				// right
				3, 2, 6,
				6, 7, 3,
				// left
				4, 5, 1,
				1, 0, 4,
				// top
				1, 5, 6,
				6, 2, 1,
				// bottom
				4, 0, 3,
				3, 7, 4,
				// back
				7, 6, 5,
				5, 4, 7

		};


Vertex planeVertices[] =
		{
				{glm::vec3(10.0f, -0.5f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,1}},
				{glm::vec3(-10.0f, -0.5f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,1}},
				{glm::vec3(-10.0f, -0.5f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,0}},
				{glm::vec3(10.0f, -0.5f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,0}}
		};



glm::vec3 lightDirection = glm::vec3(0.5f, -0.5f, -1.0f);

Vertex quadVertices[] =
		{
				{glm::vec3(-1.0f, -1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0,0}},
				{glm::vec3(1.0f, -1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1,0}},
				{glm::vec3(-1.0f, 1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0,1}},
				{glm::vec3(1.0f, 1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1,1}},

		};

GLuint quadIndices[] =
		{
				0, 1, 2,
				2, 1, 3
		};



int main(int argc, char* argv[])
{

	Window window(WIDTH, HEIGHT, "Scene");
	window.Initialize();


	OrbitalCamera camera(WIDTH, HEIGHT);


	CalculateTangentSpace(planeVertices, sizeof(planeVertices)/sizeof(planeVertices[0]), planeIndices,
			sizeof(planeIndices)/sizeof(planeIndices[0]));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	GraphicalObject quad(quadVertices, 4, quadIndices, 6);

	Skybox skybox("../Yokohama2/posx.jpg", "../Yokohama2/negx.jpg", "../Yokohama2/posy.jpg", "../Yokohama2/negy.jpg",
				  "../Yokohama2/posz.jpg",
				  "../Yokohama2/negz.jpg");

	GraphicalObject cube(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]),
			  cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(0.0f), glm::vec3(0.0f));
	GraphicalObject cube2(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]),
						 cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(0.3f, 1.05f, 0.0f));
	GraphicalObject cube3(cube_vertices2, sizeof(cube_vertices2)/sizeof(cube_vertices[2]),
						  cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(3.0f, 1.0f, -5.0f));
	GraphicalObject plane(planeVertices, 4, planeIndices, 6, {0.0f, 0.0f, 0.0f});


	GraphicalObject plane2(planeVertices, 4, planeIndices, 6, glm::vec3(0.0f, 4.0f, -9.0f), glm::vec3(F_PI/2, 0.0f, 0.0f),
						   glm::vec3(0.5f));

	Shader skyboxShader, shadowShader, cubemapReflectionShader, normalMapShader, parallaxMapShader;
	//shader compilation
	skyboxShader.Load("../src/Shaders/SkyboxShaders/SkyboxVertex.glsl", "../src/Shaders/SkyboxShaders/SkyboxFragment.glsl");
	cubemapReflectionShader.Load("../src/Shaders/SkyboxShaders/CubemapReflectionVertex.glsl",
								 "../src/Shaders/SkyboxShaders/CubemapReflectionFragment.glsl");
	shadowShader.Load("../src/Shaders/ShadowShaders/ShadowLightVertex.glsl",
					  "../src/Shaders/ShadowShaders/ShadowLightFragment.glsl");



	normalMapShader.Load("../src/Shaders/NormalMapShaders/NormalVertex.glsl",
						 "../src/Shaders/NormalMapShaders/NormalFragment.glsl");

	parallaxMapShader.Load("../src/Shaders/Parallax/ParallaxVertex.glsl",
						   "../src/Shaders/Parallax/ParallaxFragment.glsl");


	Shader geomPassShader, aoPassShader, blurPassShader;
	geomPassShader.Load("../src/Shaders/SSAO/GeometryPass/GPassVertex.glsl",
						"../src/Shaders/SSAO/GeometryPass/GPassFragment.glsl");
	aoPassShader.Load("../src/Shaders/SSAO/SSAOPass/SSAOPassVertex.glsl",
					  "../src/Shaders/SSAO/SSAOPass/SSAOPassFragment.glsl");
	blurPassShader.Load("../src/Shaders/SSAO/BlurPass/BlurVertex.glsl",
						"../src/Shaders/SSAO/BlurPass/BlurFragment.glsl");

	// !!!! ATTENTION !!!!!
	bool SoftShadows = true;
	GLint SoftShadowsSSID = glGetUniformLocation(shadowShader.Program(), "SoftShadows");
	GLint SoftShadowNMID = glGetUniformLocation(normalMapShader.Program(), "SoftShadows");
	// !!!! !!!!!!!! !!!!!!


	ShadowCamera shadowCamera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f) - lightDirection, {0.0f,0.0f,0.0f});

	//initializing shadowMap framebuffer object
	ShadowMapFBO shadowMapFBO;
	int width, height;
	glfwGetFramebufferSize(window.GetGLFWPtr(), &width, &height);
	shadowMapFBO.Init(width, height);

	Shader shadowGenShader;
	shadowGenShader.Load("../src/Shaders/ShadowShaders/ShadowGenVertex.glsl",
						 "../src/Shaders/ShadowShaders/ShadowGenFragment.glsl");



	Texture normalTex(GL_TEXTURE_2D, "../normal map/normal_map.jpg");

	Texture colorTex(GL_TEXTURE_2D, "../normal map/bricks.jpg");


	Texture normalTex2(GL_TEXTURE_2D, "../bricks/bricks2_normal.jpg");
	Texture colorTex2(GL_TEXTURE_2D, "../bricks/bricks2.jpg");
	Texture heightTex(GL_TEXTURE_2D, "../bricks/bricks2_disp.jpg");


	//initializing Lightning technique
	ShadowMapTechnique shadowMapTechnique(&shadowMapFBO, &shadowCamera);

	NormalMapTechnique normalMapTechnique(normalTex, colorTex);

	ParallaxTechnique parallaxTechnique(normalTex2, colorTex2, heightTex);

	Material material0;

	Material material;
	material.AddLightningTechnique(shadowMapTechnique);

	Material material1;
	material1.Shininess = 100.0f;
	material1.AddLightningTechnique(shadowMapTechnique);
	material1.AddLightningTechnique(normalMapTechnique);

	Material material2;
	material2.Shininess = 100.0f;
	material2.AddLightningTechnique(shadowMapTechnique);
	material2.AddLightningTechnique(parallaxTechnique);

	cube.LoadShader(shadowShader);
	cube2.LoadShader(cubemapReflectionShader);
	skybox.LoadShader(skyboxShader);

	plane.LoadShader(normalMapShader);

	plane2.LoadShader(parallaxMapShader);

	cube3.LoadShader(shadowShader);

	cube.LoadMaterial(material);
	cube2.LoadMaterial(material0);
	plane.LoadMaterial(material1);
	cube3.LoadMaterial(material);
	plane2.LoadMaterial(material2);



	FBO gBuffer, aoBuffer, blurBuffer;


	gBuffer.Init(width, height, true, GL_RGB32F);
	aoBuffer.Init(width, height, false, GL_R32F);
	blurBuffer.Init(width, height, false, GL_R32F);
	GLint posTextureUnitLocation = glGetUniformLocation(aoPassShader.Program(), "gPositionMap");
	GLint projmatLocation = glGetUniformLocation(aoPassShader.Program(), "proj");
	GLint kernelLocation = glGetUniformLocation(aoPassShader.Program(), "gKernel");


	GLint inputTextureUnitLocation = glGetUniformLocation(blurPassShader.Program(), "gColorMap");
	GLint aoTextureUnitLocation = glGetUniformLocation(shadowShader.Program(), "gAOMap");
	GLint screenSizeLocation = glGetUniformLocation(shadowShader.Program(), "ScreenSize");

	blurPassShader.UseProgram();
	glUniform1i(inputTextureUnitLocation, INPUT_TEXTURE_UNIT - GL_TEXTURE0);
	shadowShader.UseProgram();
	glUniform1i(aoTextureUnitLocation, AO_TEXTURE_UNIT - GL_TEXTURE0);
	glUniform2f(screenSizeLocation, width, height);

#define KERNEL_SIZE 128

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





	do
	{

		//Geometry pass;
		gBuffer.BindForWriting();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		cube.LoadShader(geomPassShader);
		cube.Draw(camera);
		cube2.LoadShader(geomPassShader);
		cube2.Draw(camera);
		cube3.LoadShader(geomPassShader);
		cube3.Draw(camera);
		plane.LoadShader(geomPassShader);
		plane.Draw(camera);
		plane2.LoadShader(geomPassShader);
		plane2.Draw(camera);

		//SSAO pass
		aoPassShader.UseProgram();
		camera.GetProjection(proj);
		glUniformMatrix4fv(projmatLocation, 1, GL_FALSE, &proj[0][0]);

		gBuffer.BindForReading(POSITION_TEXTURE_UNIT);
		aoBuffer.BindForWriting();
		glClear(GL_COLOR_BUFFER_BIT);
		quad.LoadShader(aoPassShader);
		quad.Draw(camera);
		//Blur pass
		aoBuffer.BindForReading(INPUT_TEXTURE_UNIT);
		blurBuffer.BindForWriting();
		glClear(GL_COLOR_BUFFER_BIT);
		quad.LoadShader(blurPassShader);
		quad.Draw(camera);


		//Lightning pass
		//ShadowMap pass
		glCullFace(GL_FRONT);
		shadowMapTechnique.WriteShadowTexture();
		cube.LoadShader(shadowGenShader);
		cube.Draw(shadowCamera);
		cube2.LoadShader(shadowGenShader);
		cube2.Draw(shadowCamera);
		cube3.LoadShader(shadowGenShader);
		cube3.Draw(shadowCamera);
		plane.LoadShader(shadowGenShader);
		plane2.Draw(shadowCamera);
		glCullFace(GL_BACK);

		//Render pass
		blurBuffer.BindForReading(AO_TEXTURE_UNIT);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


		plane.LoadShader(normalMapShader);
		plane.DrawIlluminated(camera, glm::vec4(lightDirection,1.0f));



		plane2.LoadShader(parallaxMapShader);
		plane2.DrawIlluminated(camera, glm::vec4(lightDirection, 1.0f));

		cube.LoadShader(shadowShader);
		cube.DrawIlluminated(camera, glm::vec4(lightDirection, 1.0f));

		cube3.LoadShader(shadowShader);
		cube3.DrawIlluminated(camera, glm::vec4(lightDirection,1.0f));

		skybox.Draw(camera);

		cube2.LoadShader(cubemapReflectionShader);
		cube2.Draw(camera);


// 		cube.Rotate(glm::vec3(glfwGetTime(), glfwGetTime(), glfwGetTime()));


		camera.Update(window);
//		shadowCamera.Update(window);

		// !!!!!!!
		SoftShadows = (glfwGetKey(window.GetGLFWPtr(), GLFW_KEY_Q) != GLFW_PRESS);
		shadowShader.UseProgram();
		glUniform1i(SoftShadowsSSID, SoftShadows);
		normalMapShader.UseProgram();
		glUniform1i(SoftShadowNMID, SoftShadows);
		//!!!!!!!!



		glfwSwapBuffers(window.GetGLFWPtr());
		glfwPollEvents();

	}
	while(glfwGetKey(window.GetGLFWPtr(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window.GetGLFWPtr()) == 0);

	window.Destroy();
	glfwTerminate();
	return 0;


}