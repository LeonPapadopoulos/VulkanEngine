#pragma once

#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

namespace VulkanEngine {

	class Camera {
	public:
		Camera(GLFWwindow* window);
		~Camera();

		void Update();
		void SetView(const glm::vec3& eye, const glm::vec3& lookAt);
		glm::mat4 GetViewMatrix();

		static void SetMouseWheelDelta(double delta);
		static float s_MouseWheelDelta;

	private:
		GLFWwindow* m_Window;

		glm::vec3 m_Eye = glm::vec3(5.0f, 5.0f, 0.0f);
		glm::vec3 m_LookAt = glm::vec3(-10.0f, -0.0f, 0.0f);

		glm::mat4 m_View;
		glm::vec2 m_LastMousePosition;

		float m_CameraPanSpeed = 0.005f;
		float m_CameraFreeLookSpeed = 0.002f;
		float m_CameraOrbitSpeed = 0.004f;
		float m_CameraZoomSpeed = 1.0f;
	};

	static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
}
