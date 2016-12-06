#ifndef CAMERA_H
#define CAMERA_H


#define  _USE_MATH_DEFINES //for windows
#include "math.h"


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

#include "Window.h"


#define F_PI (float)M_PI


struct Point
{
	double x, y;
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

	void GetProjection(glm::mat4& proj) const
	{
		proj = m_Projection;
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


			glViewport ( 0, 0, (GLsizei)m_Width, (GLsizei)m_Height );
		}
	}

};

class OrbitalCamera: public Camera
{

protected:

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



#endif //CAMERA_H
