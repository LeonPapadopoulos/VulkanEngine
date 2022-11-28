#pragma once

#include "../VulkanEngine.h" // -> Vertex Definition

namespace std {
	template<> struct hash < VulkanEngine::Vertex > {
		size_t operator()(VulkanEngine::Vertex const& vertex) const
		{
			return
				((hash<glm::vec3>()(vertex.pos) ^
					(hash<glm::vec3>()(vertex.color) << 1)) << 1) ^
				(hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}

namespace VulkanEngine {
	void loadModel(const std::string& modelPath, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
}