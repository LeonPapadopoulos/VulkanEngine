#pragma once

#include "Mesh.h"
#include "Camera.h"

#include <vector>
#include <string>


namespace VulkanEngine {

	struct SceneData {
		int m_MeshCount{0};
		std::vector<Mesh*> m_Meshes;
	};

	class Scene {
	public:
		Scene(GLFWwindow* window);
		~Scene();

		void Update();

		GLFWwindow* m_Window;
		Camera* m_Camera;
		SceneData* m_SceneData;
	private:
		void InitScene(GLFWwindow* window);
	};

}


