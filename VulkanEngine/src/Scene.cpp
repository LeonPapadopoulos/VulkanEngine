#include "Scene.h"
#include "Mesh.h"
#include "GridMesh.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_transform.hpp>

namespace VulkanEngine {

	Scene::Scene()
	{
		InitScene();
	}

	Scene::~Scene()
	{
		delete m_SceneData;
	}

	void Scene::InitScene()
	{
		m_SceneData = new SceneData;

		// TODO: GENERALIZE THIS UNTIL NOW HARDCODED SETUP
		float offset = 2.5f;

		Mesh* mesh1 = new Mesh();
		mesh1->LoadDefaultMesh();
		mesh1->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

		Mesh* mesh2 = new Mesh();
		mesh2->LoadDefaultMesh();
		mesh2->SetTransform(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -offset)), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));


		GridMesh* grid = new GridMesh(50, 50, 1, 1, glm::vec3(1,1,1));
		grid->m_Material->m_Shader->LoadFragmentShader("shaders/GridShaderFrag.spv");

		m_SceneData->m_Meshes.push_back(mesh1);
		m_SceneData->m_Meshes.push_back(mesh2);
		m_SceneData->m_Meshes.push_back(grid);
		m_SceneData->m_MeshCount = 3;
	}
}