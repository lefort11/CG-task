#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


#include "Window.h"
#include "Engine.h"

#define WIDTH 800
#define  HEIGHT 800

Vertex const planeVertices[] =
		{
				{glm::vec3(10.0f, -0.5f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,0}},
				{glm::vec3(-10.0f, -0.5f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,1}},
				{glm::vec3(-10.0f, -0.5f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,0}},
				{glm::vec3(10.0f, -0.5f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,1}}
		};

Vertex const planeVertices2[] =
		{
				{glm::vec3(10.0f, -10.0f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,0}},
				{glm::vec3(-10.0f, -10.0f, 10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0,1}},
				{glm::vec3(-10.0f, 10.0f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,0}},
				{glm::vec3(10.0f, 10.0f, -10.0f), {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1,1}}
		};

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


//glm::vec3 lightPosition = {-1.0f, 1.0f, 2.0f};

glm::vec3 lightInvDirection = glm::vec3(0.5f, -0.5f, -1.0f);



int main(int argc, char* argv[])
{

	Window window(WIDTH, HEIGHT, "Scene");
	window.Initialize();

	OrbitalCamera camera(WIDTH, HEIGHT);



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Skybox skybox("./Yokohama2/posx.jpg", "./Yokohama2/negx.jpg", "./Yokohama2/posy.jpg", "./Yokohama2/negy.jpg",
				  "./Yokohama2/posz.jpg",
				  "./Yokohama2/negz.jpg");

	GraphicalObject cube(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]),
			  cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(0.0f, 0.0f, 0.0f));


	GraphicalObject cube2(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]),
						 cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(1.0f, 1.0f, 0.0f));


	GraphicalObject cube3(cube_vertices2, sizeof(cube_vertices2)/sizeof(cube_vertices[2]),
						  cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]), glm::vec3(1.0f, 1.0f, -5.0f));


	GraphicalObject plane(planeVertices, 4, planeIndices, 6, {0.0f, 0.0f, 0.0f});
	GraphicalObject plane2(planeVertices2, 4, planeIndices, 6, {0.0f, 0.0f, -5.0f});


	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


	Shader blinnShader, skyboxShader, shadowShader, cubemapReflectionShader;
	//shader compilation
//	blinnShader.Load("./src/Shaders/BlinnShaders/BlinnVertex.glsl", "./src/Shaders/BlinnShaders/BlinnFragment.glsl");
	skyboxShader.Load("./src/Shaders/SkyboxShaders/SkyboxVertex.glsl", "./src/Shaders/SkyboxShaders/SkyboxFragment.glsl");
	cubemapReflectionShader.Load("./src/Shaders/SkyboxShaders/CubemapReflectionVertex.glsl",
								 "./src/Shaders/SkyboxShaders/CubemapReflectionFragment.glsl");
	shadowShader.Load("./src/Shaders/ShadowShaders/ShadowLightVertex.glsl",
					  "./src/Shaders/ShadowShaders/ShadowLightFragment.glsl");

	cube.LoadShader(shadowShader);
	cube2.LoadShader(cubemapReflectionShader);
	skybox.LoadShader(skyboxShader);

	plane.LoadShader(shadowShader);
	plane2.LoadShader(shadowShader);

	cube3.LoadShader(shadowShader);

	ShadowCamera shadowCamera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f) - lightInvDirection, {0.0f,0.0f,0.0f});

	//initializing shadowMap framebuffer object
	ShadowMapFBO shadowMapFBO;
	int width, height;
	glfwGetFramebufferSize(window.GetGLFWPtr(), &width, &height);
	shadowMapFBO.Init(width, height);

	Shader shadowGenShader;
	shadowGenShader.Load("./src/Shaders/ShadowShaders/ShadowGenVertex.glsl",
						 "./src/Shaders/ShadowShaders/ShadowGenFragment.glsl");

	//initializing shadowmap technique
	ShadowMapTechnique shadowMapTechnique(&shadowMapFBO);
	shadowMapTechnique.Init(shadowShader);


	do
	{


		//ShadowMap pass
		glCullFace(GL_FRONT);

		shadowMapTechnique.WriteShadowTexture();
		cube.LoadShader(shadowGenShader);
		cube.Draw(shadowCamera);
		cube2.LoadShader(shadowGenShader);
		cube2.Draw(shadowCamera);
		cube3.LoadShader(shadowGenShader);
		cube3.Draw(shadowCamera);


		glCullFace(GL_BACK);

		//Render pass
		shadowMapTechnique.ReadShadowTexture(GL_TEXTURE0);
		shadowMapTechnique.LoadLightBiasMVP(shadowShader, shadowCamera, plane);// loads to shadow shader uniform light bias mvp
		plane.DrawIlluminated(camera, glm::vec4(lightInvDirection,1.0f));


		cube.LoadShader(shadowShader);
		cube.DrawIlluminated(camera, glm::vec4(lightInvDirection, 1.0f));

		shadowMapTechnique.LoadLightBiasMVP(shadowShader,shadowCamera, cube3);
		cube3.LoadShader(shadowShader);
		cube3.DrawIlluminated(camera, glm::vec4(lightInvDirection,1.0f));
		//shadowShader.UseProgram();
		//shadowMapTechnique.LoadLightBiasMVP(shadowCamera, plane2);// loads to shadow shader uniform light bias mvp
		//plane2.DrawIlluminated(camera, glm::vec4(lightPosition,1.0f));


		skybox.Draw(camera);

		cube2.LoadShader(cubemapReflectionShader);
		cube2.Draw(camera);

		camera.Update(window);
		shadowCamera.Update(window);

		glfwSwapBuffers(window.GetGLFWPtr());
		glfwPollEvents();

	}
	while(glfwGetKey(window.GetGLFWPtr(), GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window.GetGLFWPtr()) == 0);


	window.Destroy();
	glfwTerminate();

	return 0;


}