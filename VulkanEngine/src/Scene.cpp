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

		float offset = 2.5f;

		Mesh* mesh1 = new Mesh();
		mesh1->LoadDefaultMesh();
		mesh1->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		Mesh* mesh2 = new Mesh();
		mesh2->LoadDefaultMesh();
		mesh2->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));


		GridMesh* grid = new GridMesh(50, 50, 1, 1, glm::vec4(0.1f, 0.1f, 0.1f, 1));
		grid->m_Material->m_Shader->LoadFragmentShader("shaders/GridShaderFrag.spv");

		m_SceneData->m_Meshes.push_back(mesh1);
		m_SceneData->m_Meshes.push_back(mesh2);
		m_SceneData->m_Meshes.push_back(grid);
		m_SceneData->m_MeshCount = 3;
	}
}