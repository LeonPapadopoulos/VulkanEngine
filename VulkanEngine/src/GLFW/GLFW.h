#pragma once

#include <GLFW/glfw3.h>

class GLFW {

public:
	GLFW();
	void initWindow(uint32_t width, uint32_t height, const char* name);
	
	GLFWwindow& GetWindow();

	GLFW(const GLFW&) = delete;
private:
	GLFWwindow* window;

};