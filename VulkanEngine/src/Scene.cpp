#include "Scene.h"
#include "Mesh.h"
#include "GridMesh.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_transform.hpp>

namespace VulkanEngine {

	Scene::Scene(GLFWwindow* window)
		: m_Window(window)
	{
		InitScene(window);
	}

	Scene::~Scene()
	{
		for (int i = 0; i < (*m_SceneData).m_Meshes.size(); i++)
		{
			delete (*m_SceneData).m_Meshes[i];
		}

		delete m_SceneData;
	}

	void Scene::Update()
	{
		m_Camera->Update();
	}

	// TODO: Make it possible to author Scene directly in viewport via Hierarchical Node Setup
	void Scene::InitScene(GLFWwindow* window)
	{
		m_Camera = new Camera(window);
		m_SceneData = new SceneData;

		float offset = 2.5f;

		std::string meshFilepath = "models/viking_room.obj";
		std::string meshMaterialTexturePath = "textures/viking_room.png";
		std::string meshVertShaderPath = "shaders/vert.spv";
		std::string meshFragShaderPath = "shaders/frag.spv";

		std::shared_ptr<Shader> meshMaterialShader = std::make_shared<Shader>(meshVertShaderPath, meshFragShaderPath);

		// TODO: Make sharing ressources like identical Materials / Textures etc. possible. Will need Ressource cleanup refactoring necessary!

		// Dummy Loaded Mesh 1
		std::shared_ptr<Texture> mesh1MaterialTexture = std::make_shared<Texture>(meshMaterialTexturePath);
		std::shared_ptr<Material> mesh1Material = std::make_shared<Material>(meshMaterialShader, mesh1MaterialTexture);
		Mesh* mesh1 = new Mesh(meshFilepath, mesh1Material);
		mesh1->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		// Dummy Loaded Mesh 2
		std::shared_ptr<Texture> mesh2MaterialTexture = std::make_shared<Texture>(meshMaterialTexturePath);
		std::shared_ptr<Material> mesh2Material = std::make_shared<Material>(meshMaterialShader, mesh2MaterialTexture);
		Mesh* mesh2 = new Mesh(meshFilepath, mesh2Material);
		mesh2->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		// Blender Default Cube
		std::shared_ptr<Shader> cubeMeshMaterialShader = std::make_shared<Shader>(meshVertShaderPath, meshFragShaderPath);
		std::shared_ptr<Texture> cubeMeshMaterialTexture = std::make_shared<Texture>("textures/black.png");
		std::shared_ptr<Material> cubeMeshMaterial = std::make_shared<Material>(cubeMeshMaterialShader, cubeMeshMaterialTexture);
		Mesh* cubeMesh = new Mesh("models/cube.obj", cubeMeshMaterial);
		cubeMesh->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, 3.0f, 0.0f)), glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		// Blender Monkey
		std::shared_ptr<Shader> monkeyMeshMaterialShader = std::make_shared<Shader>(meshVertShaderPath, "shaders/frag.spv");
		std::shared_ptr<Texture> monkeyMeshMaterialTexture = std::make_shared<Texture>("textures/neon.png");
		std::shared_ptr<Material> monkeyMeshMaterial = std::make_shared<Material>(monkeyMeshMaterialShader, monkeyMeshMaterialTexture);
		Mesh* monkeyMesh = new Mesh("models/monkey.obj", monkeyMeshMaterial);
		monkeyMesh->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 3.0f, 0.0f)), glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		// Generated GridMesh
		std::shared_ptr<Shader> gridMeshMaterialShader = std::make_shared<Shader>("shaders/vert.spv", "shaders/GridShaderFrag.spv");
		std::shared_ptr<Texture> gridMeshMaterialTexture = std::make_shared<Texture>("textures/viking_room.png");
		std::shared_ptr<Material> gridMeshMaterial = std::make_shared<Material>(gridMeshMaterialShader, gridMeshMaterialTexture);
		GridMesh* grid = new GridMesh(gridMeshMaterial, 50, 50, 1, 1, glm::vec4(0.1f, 0.1f, 0.1f, 1));

		m_SceneData->m_Meshes.push_back(mesh1);
		m_SceneData->m_Meshes.push_back(mesh2);
		m_SceneData->m_Meshes.push_back(cubeMesh);
		m_SceneData->m_Meshes.push_back(monkeyMesh);
		m_SceneData->m_Meshes.push_back(grid);
		m_SceneData->m_MeshCount = m_SceneData->m_Meshes.size();
	}
}