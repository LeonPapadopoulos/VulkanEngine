#pragma once

#include <glm/glm.hpp>

namespace VulkanEngine{

	struct UniformBufferGlobal
	{
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
		alignas(16) glm::mat4 viewProj;
	};

	struct UniformBufferPerModel {
		alignas(16) glm::mat4 model;
	};

}