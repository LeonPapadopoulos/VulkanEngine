#include "Camera.h"
#include "glm/glm.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "glm/gtc/matrix_access.hpp"
#include "GLFW/glfw3.h"
#include "Maths/Maths.h"

#include <iostream>

namespace VulkanEngine {

	float Camera::s_MouseWheelDelta = 0;

	Camera::Camera(GLFWwindow* window)
	{
		m_Window = window;

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		m_LastMousePosition = glm::vec2(xPos, yPos);

		SetView(m_Eye, m_LookAt);
		glfwSetScrollCallback(window, MouseScrollCallback);
	}

	Camera::~Camera()
	{
	}

	void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Camera::SetMouseWheelDelta(yoffset);
	}

	void Camera::Update()
	{
		// Get current Camera Details
		glm::vec3 camRight = glm::row(m_View, 0);
		glm::vec3 camUp = glm::row(m_View, 1);
		glm::vec3 camForward = - glm::row(m_View, 2);

		glm::vec3 moveDir = glm::vec3(0,0,0);
		glm::vec3 lookDir = m_LookAt - m_Eye;
		float distance = glm::length(lookDir);

		//ZOOM
		if (glm::abs(Camera::s_MouseWheelDelta) >= FLT_EPSILON)
		{
			distance += Camera::s_MouseWheelDelta * m_CameraZoomSpeed;
			m_Eye = m_LookAt - distance * glm::normalize(lookDir);
			Camera::s_MouseWheelDelta = 0;
		}

		//CAMERA PANNING
		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		{
			moveDir += camForward;
		}
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		{
			moveDir += -camRight;
		}
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		{
			moveDir += -camForward;
		}
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		{
			moveDir += camRight;
		}

		if (glm::length(moveDir) >= FLT_EPSILON)
		{
			moveDir = glm::normalize(moveDir);
		}
		moveDir *= m_CameraPanSpeed;
		m_Eye += moveDir;
		m_LookAt += moveDir;

		// UPDATE CURSOR INFO
		double xPos, yPos;
		glfwGetCursorPos(m_Window, &xPos, &yPos);
		glm::vec2 currentMousePosition = glm::vec2(xPos, yPos);

		// CAMERA FREE LOOK AROUND ITSELF
		if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			// TODO: KEEP FREE LOOK SPEED CONSTANT ACROSS LATERAL AND DIAGONAL MOVEMENT
			glm::vec2 mousePositionDelta = currentMousePosition - m_LastMousePosition;
			float mousePositionDeltaDistance = glm::length(mousePositionDelta);
			if (mousePositionDeltaDistance >= FLT_EPSILON)
			{
				mousePositionDelta = glm::normalize(mousePositionDelta);
			}

			lookDir = glm::rotate(lookDir, -m_CameraFreeLookSpeed * mousePositionDelta.x, camUp);
			lookDir = glm::rotate(lookDir, -m_CameraFreeLookSpeed * mousePositionDelta.y, camRight);
			m_LookAt = m_Eye + lookDir;
		}

		// CAMERA ORBIT AROUND LOOKAT
		if (glfwGetKey(m_Window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			// TODO: KEEP FREE LOOK SPEED CONSTANT ACROSS LATERAL AND DIAGONAL MOVEMENT
			glm::vec2 mousePositionDelta = currentMousePosition - m_LastMousePosition;
			float mousePositionDeltaDistance = glm::length(mousePositionDelta);
			if (mousePositionDeltaDistance >= FLT_EPSILON)
			{
				mousePositionDelta = glm::normalize(mousePositionDelta);
			}

			lookDir = glm::rotate(lookDir, -m_CameraOrbitSpeed * mousePositionDelta.x, camUp);
			lookDir = glm::rotate(lookDir, -m_CameraOrbitSpeed * mousePositionDelta.y, camRight);

			m_Eye = m_LookAt - lookDir;
		}

		SetView(m_Eye, m_LookAt);
		m_LastMousePosition = currentMousePosition;
	}

	void Camera::SetView(const glm::vec3& eye, const glm::vec3& lookAt)
	{
		m_View = glm::lookAtRH(eye, lookAt, glm::vec3(0,1,0));
	}

	void Camera::SetMouseWheelDelta(double delta)
	{
		Camera::s_MouseWheelDelta = delta;
	}

	glm::mat4 Camera::GetViewMatrix() 
	{ 
		return m_View; 
	}
}