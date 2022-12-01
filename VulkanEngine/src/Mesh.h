#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Vertex.h"

#include <string>
#include <vector>
#include <memory>

namespace VulkanEngine {

	class Texture {
	public:
		Texture(const std::string& filepath);

		std::string m_FilePath;

		uint32_t m_MipLevels;
		VkImage m_TextureImage;
		VkDeviceMemory m_TextureImageMemory;
		VkImageView m_TextureImageView;
		VkSampler m_TextureSampler;
	private:

	};
	class TextureLibrary {

	};


	class Shader {
	public:
		Shader(const std::string& vertShader, const std::string& fragShader);

		std::vector<char> m_VertShaderCode;
		std::vector<char> m_FragShaderCode;

	private:

	};

	class Material {
	public:
		Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

		std::shared_ptr<Texture> m_Texture;
		std::shared_ptr<Shader> m_Shader;

		VkPipeline m_GraphicsPipeline;
		VkPipelineLayout m_GraphicsPipelineLayout;

		// Per Material Data, e.g. Custom Data to be decided on
		//std::vector<VkBuffer> m_UniformBuffers;
		//std::vector<VkDeviceMemory> m_UniformBuffersMemory;
		//std::vector<void*> m_UniformBuffersMapped;
	private:

	};

	class MaterialLibrary {
	public:
		MaterialLibrary();

		//void AddMaterial(Material& material);
		//std::shared_ptr<Material*> GetMaterial(const std::string& materialName);

		//std::unordered_map<const std::string&, Material> m_Materials;
	};

	class Mesh {

	public:
		Mesh(std::shared_ptr<Material> material);
		Mesh(const std::string& filepath, std::shared_ptr<Material> material);
		virtual ~Mesh();

		void SetTransform(glm::mat4 transform);

		glm::mat4 m_Transform = glm::mat4(1.0);

		std::shared_ptr<Material> m_Material;

		VkPrimitiveTopology m_Topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

		VkBuffer m_VertexBuffer;
		VkBuffer m_IndexBuffer;
		VkDeviceMemory m_VertexBufferMemory;
		VkDeviceMemory m_IndexBufferMemory;

		// One Buffer per Frame in Flight
		std::vector<VkBuffer> m_UniformBuffers;
		std::vector<VkDeviceMemory> m_UniformBuffersMemory;
		std::vector<void*> m_UniformBuffersMapped;

		// One Descriptor Set per frame in Flight
		std::vector<VkDescriptorSet> m_DescriptorSets;

		std::string m_Filepath;
	private:

	};
}
