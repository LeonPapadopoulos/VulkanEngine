#pragma once

#include "Mesh.h"

#include <vector>
#include <string>


namespace VulkanEngine {

	struct SceneData {
		int m_MeshCount{0};
		std::vector<Mesh*> m_Meshes;
	};

	class Scene {
	public:
		Scene();
		~Scene();

		SceneData* m_SceneData;
	private:
		void InitScene();
	};

}


