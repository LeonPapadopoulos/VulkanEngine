#pragma once

#include "Mesh.h"

namespace VulkanEngine {

	class GridMesh : public Mesh
	{
	public:
		GridMesh(uint8_t numSegmentsX, uint8_t numSegmentsZ, float spacePerSegmentX, float spacePerSegmentZ, glm::vec3 gridColor);
		~GridMesh();


	private:
		void createGridMesh(uint8_t numSegmentsX, uint8_t numSegmentsZ, float spacePerSegmentX, float spacePerSegmentZ, glm::vec3 gridColor);
		void createTestMesh();

		uint8_t m_NumSegmentsX;
		uint8_t m_NumSegmentsZ;

		float m_SpacePerSegmentX;
		float m_SpacePerSegmentZ;
	};

}