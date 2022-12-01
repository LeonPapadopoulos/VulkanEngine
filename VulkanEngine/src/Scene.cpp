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

		//const std::string c_DefaultVertShaderPath = "shaders/vert.spv";
		//const std::string c_DefaultFragShaderPath = "shaders/frag.spv";

		float offset = 2.5f;

		std::string meshFilepath = "models/viking_room.obj";
		std::string meshMaterialTexturePath = "textures/viking_room.png";
		std::string meshVertShaderPath = "shaders/vert.spv";
		std::string meshFragShaderPath = "shaders/frag.spv";

		Material* mesh1Material = new Material(new Shader(meshVertShaderPath, meshFragShaderPath), new Texture(meshMaterialTexturePath));
		Mesh* mesh1 = new Mesh(meshFilepath, mesh1Material);
		mesh1->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		Material* mesh2Material = new Material(new Shader(meshVertShaderPath, meshFragShaderPath), new Texture(meshMaterialTexturePath));
		Mesh* mesh2 = new Mesh(meshFilepath, mesh2Material);
		mesh2->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		Material* gridMeshMaterial = new Material(new Shader("shaders/vert.spv", "shaders/GridShaderFrag.spv"), new Texture("textures/viking_room.png"));
		GridMesh* grid = new GridMesh(gridMeshMaterial, 50, 50, 1, 1, glm::vec4(0.1f, 0.1f, 0.1f, 1));

		m_SceneData->m_Meshes.push_back(mesh1);
		m_SceneData->m_Meshes.push_back(mesh2);
		m_SceneData->m_Meshes.push_back(grid);
		m_SceneData->m_MeshCount = 3;
	}
}