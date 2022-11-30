#pragma once
#include "glm/glm.hpp"

namespace VulkanEngine {

#define VECTOR3_ZERO glm::vec3(0.0, 0.0, 0.0);
#define VECTOR3_UP glm::vec3(0.0, 1.0, 0.0);
#define VECTOR3_RIGHT glm::vec3(1.0, 0.0, 0.0);
#define VECTOR3_FORWARD glm::vec3(0.0, 0.0, 1.0);

	//struct Vector3 {
	//	float x, y, z;
	//};

	//struct Mat4x4 {
	//	float M00,
	//	float M01,
	//	float M02,
	//	float M03,
	//	float M10,
	//	float M11,
	//	float M12,
	//	float M13,
	//	float M20,
	//	float M21,
	//	float M22,
	//	float M23,
	//};

}