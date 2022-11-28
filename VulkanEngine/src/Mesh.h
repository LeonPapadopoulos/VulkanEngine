#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>	// -> VkStructs

#include "Vertex.h"

#include <string>
#include <vector>

namespace VulkanEngine {

	class Texture {
	public:
		Texture();

		std::string m_FilePath;

		uint32_t m_MipLevels;
		VkImage m_TextureImage;
		VkDeviceMemory m_TextureImageMemory;
		VkImageView m_TextureImageView;
		VkSampler m_TextureSampler;
	private:
		void LoadDefaultTexture();
		const std::string c_DefaultTextureFilePath = "textures/viking_room.png";
	};
	class TextureLibrary {

	};


	class Shader {
	public:
		Shader();

		std::vector<char> m_VertShaderCode;
		std::vector<char> m_FragShaderCode;
		void LoadFragmentShader(const std::string& shaderDirectory);

	private:
		void LoadDefaultShader();

		const std::string c_DefaultVertShaderPath = "shaders/vert.spv";
		const std::string c_DefaultFragShaderPath = "shaders/frag.spv";

	};

	class Material {
	public:
		Material();

		Texture* m_Texture;
		Shader* m_Shader;

		VkPipeline m_GraphicsPipeline; // (Shader / DescriptorSetLayout / Renderpass - Dependent)
		VkPipelineLayout m_GraphicsPipelineLayout; // (DescriptorSetLayout - dependent)

		// Per Material Data, e.g. Custom Data to be decided on
		//std::vector<VkBuffer> m_UniformBuffers;
		//std::vector<VkDeviceMemory> m_UniformBuffersMemory;
		//std::vector<void*> m_UniformBuffersMapped;
	private:
		void LoadDefaultMaterial();
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
		Mesh();
		virtual ~Mesh();

		void LoadDefaultMesh();
		void SetTransform(glm::mat4 transform);

		glm::mat4 m_Transform = glm::mat4(1.0);

		Material* m_Material;

		VkPrimitiveTopology m_Topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

		std::vector<Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

		VkBuffer m_VertexBuffer;
		VkBuffer m_IndexBuffer;
		VkDeviceMemory m_VertexBufferMemory;
		VkDeviceMemory m_IndexBufferMemory;

		// Per Mesh Data, e.g. Transform. Vectors for Frames in Flight
		std::vector<VkBuffer> m_UniformBuffers;
		std::vector<VkDeviceMemory> m_UniformBuffersMemory;
		std::vector<void*> m_UniformBuffersMapped;

		std::vector<VkDescriptorSet> m_DescriptorSets; // 1 per Frame in Flight | 1 global ubo, 1 model ubo, 1 texture per set
		
		const std::string c_DefaultMeshPath = "models/viking_room.obj";

	private:
		void CreateBuffers();

	};
}
