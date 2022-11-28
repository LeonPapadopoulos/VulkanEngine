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
		//glm::mat4 GetProjectionMatrix();
		//glm::mat4 GetViewProjectionMatrix();

		static void SetMouseWheelDelta(double delta);
		static float s_MouseWheelDelta;

	private:
		//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		GLFWwindow* m_Window;

		glm::vec3 m_Eye = glm::vec3(5.0f, 2.5f, 0.0f);
		glm::vec3 m_LookAt = glm::vec3(0.0f, -5.0f, 0.0f);

		glm::mat4 m_View;
		//glm::mat4 m_Projection;
		glm::vec2 m_LastMousePosition;

		float m_CameraPanSpeed = 0.005f;
		float m_CameraFreeLookSpeed = 0.001f;
		float m_CameraOrbitSpeed = 0.005f;
		float m_CameraZoomSpeed = 1.0f;
	};

	static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
}
