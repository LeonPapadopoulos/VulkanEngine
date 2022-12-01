#pragma once

#include "Mesh.h"

namespace VulkanEngine {

	class GridMesh : public Mesh
	{
	public:
		GridMesh(Material* material, uint8_t numSegmentsX, uint8_t numSegmentsZ, float spacePerSegmentX, float spacePerSegmentZ, glm::vec3 gridColor);
		~GridMesh();


	private:
		void createGridMesh(uint8_t numSegmentsX, uint8_t numSegmentsZ, float spacePerSegmentX, float spacePerSegmentZ, glm::vec3 gridColor);
		void createTestMesh();

		uint8_t m_NumSegmentsX;
		uint8_t m_NumSegmentsZ;

		float m_SpacePerSegmentX;
		float m_SpacePerSegmentZ;

		glm::vec3 m_GridColor;
		glm::vec3 m_XAxisColor = glm::vec3(0.8f, 0.2f, 0.2f);
		glm::vec3 m_ZAxisColor = glm::vec3(0.2f, 0.2f, 0.8f);
	};
}