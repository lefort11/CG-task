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


Vertex planeVertices[] =
		{
				{glm::vec3(10.0f, -0.5f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,1}},
				{glm::vec3(-10.0f, -0.5f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,1}},
				{glm::vec3(-10.0f, -0.5f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,0}},
				{glm::vec3(10.0f, -0.5f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,0}}
		};



glm::vec3 lightDirection = glm::vec3(1.0f, -1.0f, -1.0f);

Vertex SSAOTechnique::quadVertices[] =
		{
				{glm::vec3(-1.0f, -1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0,0}},
				{glm::vec3(1.0f, -1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1,0}},
				{glm::vec3(-1.0f, 1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0,1}},
				{glm::vec3(1.0f, 1.0f, 0.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1,1}},

		};

GLuint SSAOTechnique::quadIndices[] =
		{
				0, 1, 2,
				2, 1, 3
		};



int main(int argc, char* argv[])
{

	Window window(WIDTH, HEIGHT, "Scene");
	window.Initialize();

	std::vector<Vertex> cubeVertices;
	std::vector<Vertex> jeepVertices;

	LoadOBJ("./res/cube.obj", cubeVertices);
	//LoadOBJ("/Users/Gleb/Desktop/mashgraph/src/cube.obj", cubeVertices);
	LoadOBJ("./res/jeep.obj", jeepVertices);

	OrbitalCamera camera(WIDTH, HEIGHT);

	CalculateTangentSpace(planeVertices, sizeof(planeVertices)/sizeof(planeVertices[0]), planeIndices,
			sizeof(planeIndices)/sizeof(planeIndices[0]));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	Skybox skybox("./res/Yokohama2/posx.jpg", "./res/Yokohama2/negx.jpg",
				  "./res/Yokohama2/posy.jpg", "./res/Yokohama2/negy.jpg",
				  "./res//Yokohama2/posz.jpg",
				  "./res/Yokohama2/negz.jpg");

/*	GraphicalObject cube(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]),
			  cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(0.0f), glm::vec3(0.0f));
	GraphicalObject cube2(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]),
						 cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(0.3f, 1.05f, 0.0f));
	GraphicalObject cube3(cube_vertices2, sizeof(cube_vertices2)/sizeof(cube_vertices[2]),
						  cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(3.0f, 1.0f, -5.0f)); */

	GraphicalObject cube(cubeVertices, glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.5f));
	GraphicalObject cube2(cubeVertices, glm::vec3(0.3f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f));
	GraphicalObject cube3(cubeVertices, glm::vec3(3.0f, 1.0f, -3.0f), glm::vec3(0.0f), glm::vec3(1.5f));
	GraphicalObject plane(planeVertices, 4, planeIndices, 6, {0.0f, 0.0f, 0.0f});

	GraphicalObject jeep(jeepVertices, glm::vec3(-3.0f, -0.5f, 0.0f), glm::vec3(0.0f), glm::vec3(0.005f));

	GraphicalObject plane2(planeVertices, 4, planeIndices, 6, glm::vec3(0.0f, 4.0f, -9.0f), glm::vec3(F_PI/2, 0.0f, 0.0f),
						   glm::vec3(0.5f));

	Shader skyboxShader, shadowShader, cubemapReflectionShader, normalMapShader, parallaxMapShader;
	//shader compilation
	skyboxShader.Load("./Shaders/SkyboxShaders/SkyboxVertex.glsl", "./Shaders/SkyboxShaders/SkyboxFragment.glsl");
	cubemapReflectionShader.Load("./Shaders/SkyboxShaders/CubemapReflectionVertex.glsl",
								 "./Shaders/SkyboxShaders/CubemapReflectionFragment.glsl");
	shadowShader.Load("./Shaders/ShadowShaders/ShadowLightVertex.glsl",
					  "./Shaders/ShadowShaders/ShadowLightFragment.glsl");



	normalMapShader.Load("./Shaders/NormalMapShaders/NormalVertex.glsl",
						 "./Shaders/NormalMapShaders/NormalFragment.glsl");

	parallaxMapShader.Load("./Shaders/Parallax/ParallaxVertex.glsl",
						   "./Shaders/Parallax/ParallaxFragment.glsl");
	Shader geomPassShader, aoPassShader, blurPassShader;
	geomPassShader.Load("./Shaders/SSAO/GeometryPass/GPassVertex.glsl",
						"./Shaders/SSAO/GeometryPass/GPassFragment.glsl");
	aoPassShader.Load("./Shaders/SSAO/SSAOPass/SSAOPassVertex.glsl",
					  "./Shaders/SSAO/SSAOPass/SSAOPassFragment.glsl");
	blurPassShader.Load("./Shaders/SSAO/BlurPass/BlurVertex.glsl",
						"./Shaders/SSAO/BlurPass/BlurFragment.glsl");

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
	shadowGenShader.Load("./Shaders/ShadowShaders/ShadowGenVertex.glsl",
						 "./Shaders/ShadowShaders/ShadowGenFragment.glsl");

	Texture normalTex(GL_TEXTURE_2D, "./res/normal map/normal_map.jpg");

	Texture colorTex(GL_TEXTURE_2D, "./res/normal map/bricks.jpg");

	Texture normalTex2(GL_TEXTURE_2D, "./res/bricks/bricks2_normal.jpg");
	Texture colorTex2(GL_TEXTURE_2D, "./res/bricks/bricks2.jpg");
	Texture heightTex(GL_TEXTURE_2D, "./res/bricks/bricks2_disp.jpg");


	//initializing Lightning technique
	ShadowMapTechnique shadowMapTechnique(&shadowMapFBO, &shadowCamera);

	NormalMapTechnique normalMapTechnique(normalTex, colorTex);

	ParallaxTechnique parallaxTechnique(normalTex2, colorTex2, heightTex);

	Material material0;

	Material material;
	material.AddLightningTechnique(shadowMapTechnique);
	material.Shininess = 10.0f;

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
	jeep.LoadShader(shadowShader);

	cube.LoadMaterial(material);
	cube2.LoadMaterial(material0);
	plane.LoadMaterial(material1);
	cube3.LoadMaterial(material);
	plane2.LoadMaterial(material2);
	jeep.LoadMaterial(material);

	FBO gBuffer, aoBuffer, blurBuffer;
	gBuffer.Init(width, height, true, GL_RGB32F);
	aoBuffer.Init(width, height, false, GL_R32F);
	blurBuffer.Init(width, height, false, GL_R32F);

	SSAOTechnique ssaoTechnique(gBuffer, aoBuffer, blurBuffer);
	ssaoTechnique.Init(geomPassShader, aoPassShader, blurPassShader, shadowShader, camera, width, height);


	do
	{
		//Geometry pass;
		ssaoTechnique.GeometryPassInit();

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
		jeep.LoadShader(geomPassShader);
		jeep.Draw(camera);

		//SSAO pass
		ssaoTechnique.SSAOPass();
		//Blur pass
		ssaoTechnique.BlurPass();

		//Lightning pass
		ssaoTechnique.LightningPassInit();
		//ShadowMap pass
		shadowMapTechnique.ShadowMapPassInit();
		cube.LoadShader(shadowGenShader);
		cube.Draw(shadowCamera);
		cube2.LoadShader(shadowGenShader);
		cube2.Draw(shadowCamera);
		cube3.LoadShader(shadowGenShader);
		cube3.Draw(shadowCamera);
		plane.LoadShader(shadowGenShader);
		plane2.Draw(shadowCamera);
		jeep.LoadShader(shadowGenShader);
		jeep.Draw(shadowCamera);

		//Render pass
		shadowMapTechnique.RenderPassInit();

		plane.LoadShader(normalMapShader);
		plane.DrawIlluminated(camera, glm::vec4(lightDirection,1.0f));

		plane2.LoadShader(parallaxMapShader);
		plane2.DrawIlluminated(camera, glm::vec4(lightDirection, 1.0f));

		jeep.LoadShader(shadowShader);
		jeep.DrawIlluminated(camera, glm::vec4(lightDirection,1.0f));

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