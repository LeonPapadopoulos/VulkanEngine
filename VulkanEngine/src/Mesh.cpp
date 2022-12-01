#include "Mesh.h"
#include "TinyOBJ/tinyOBJ_Helpers.h"
#include "VulkanEngine.h"
#include "Vulkan/VulkanEngine_Helpers.h"


namespace VulkanEngine {

	Texture::Texture(const std::string& filepath)
	{
		m_FilePath = filepath;
	}
}

namespace VulkanEngine {

	Shader::Shader(const std::string& vertShader, const std::string& fragShader)
	{
		m_VertShaderCode = readFile(vertShader);
		m_FragShaderCode = readFile(fragShader);
	}
}


namespace VulkanEngine {

	Material::Material(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	{
		m_Texture = texture;
		m_Shader = shader;
	}
}


namespace VulkanEngine {

	MaterialLibrary::MaterialLibrary()
	{

	}

	//std::shared_ptr<Material*> MaterialLibrary::GetMaterial(const std::string& materialName)
	//{

	//}
}


namespace VulkanEngine {

	Mesh::Mesh(std::shared_ptr<Material> material)
	{
		m_Material = material;
	}

	Mesh::Mesh(const std::string& filepath, std::shared_ptr<Material> material)
	{
		m_Filepath = filepath;
		m_Material = material;
		loadModel(filepath, m_Vertices, m_Indices);
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::SetTransform(glm::mat4 transform)
	{
		m_Transform = transform;
	}
}



