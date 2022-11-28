#include "Mesh.h"
#include "TinyOBJ/tinyOBJ_Helpers.h"
#include "VulkanEngine.h"
#include "Vulkan/VulkanEngine_Helpers.h"


namespace VulkanEngine {

	Texture::Texture()
	{
		LoadDefaultTexture();
	}

	void Texture::LoadDefaultTexture()
	{
		m_FilePath = c_DefaultTextureFilePath;
	}
}

namespace VulkanEngine {

	Shader::Shader()
	{
		LoadDefaultShader();
	}

	void Shader::LoadFragmentShader(const std::string& shaderDirectory)
	{
		m_FragShaderCode = readFile(shaderDirectory);
	}

	void Shader::LoadDefaultShader()
	{
		m_VertShaderCode = readFile(c_DefaultVertShaderPath);
		m_FragShaderCode = readFile(c_DefaultFragShaderPath);
	}
}


namespace VulkanEngine {

	Material::Material()
	{
		LoadDefaultMaterial();
	}

	void Material::LoadDefaultMaterial()
	{
		m_Texture = new Texture();
		m_Shader = new Shader();
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

	Mesh::Mesh()
	{
		m_Material = new Material();
	}

	Mesh::~Mesh()
	{
		// TODO
		// Destroy Vertex & Index Buffer
		// Free Vertex & Index Buffer Memory
	}

	void Mesh::LoadDefaultMesh()
	{
		loadModel(c_DefaultMeshPath, m_Vertices, m_Indices);
	}

	void Mesh::SetTransform(glm::mat4 transform)
	{
		m_Transform = transform;
	}

	void Mesh::CreateBuffers()
	{
		// TODO
	}
}



