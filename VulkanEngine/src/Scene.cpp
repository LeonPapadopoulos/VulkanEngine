#include "Scene.h"
#include "Mesh.h"


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
		Mesh* mesh1 = new Mesh();
		Mesh* mesh2 = new Mesh();
		m_SceneData->m_Meshes.push_back(mesh1);
		m_SceneData->m_Meshes.push_back(mesh2);
		m_SceneData->m_MeshCount = 2;
	}
}