#include "GridMesh.h"
#include "Mesh.h"

namespace VulkanEngine {

	GridMesh::GridMesh(uint8_t numSegmentsX, uint8_t numSegmentsZ, float spacePerSegmentX, float spacePerSegmentZ, glm::vec3 gridColor)
		: m_NumSegmentsX(numSegmentsX), m_NumSegmentsZ(numSegmentsZ), m_SpacePerSegmentX(spacePerSegmentX), m_SpacePerSegmentZ(spacePerSegmentZ)
	{
		createGridMesh(numSegmentsX, numSegmentsZ, spacePerSegmentX, spacePerSegmentZ, gridColor);
		m_Topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		//createTestMesh();
	}

	GridMesh::~GridMesh()
	{
	}

	void GridMesh::createGridMesh(uint8_t numSegmentsX, uint8_t numSegmentsZ, float spacePerSegmentX, float spacePerSegmentZ, glm::vec3 gridColor)
	{
		Vertex vertex{};
		vertex.color = gridColor;
		vertex.texCoord = glm::vec2(0, 0);

		int index = 0;

		for (uint32_t i = 0; i < numSegmentsX; i++)
		{
			for (uint32_t j = 0; j < 2; j++)
			{
				vertex.pos = glm::vec3(
					(-m_NumSegmentsX * spacePerSegmentX) / 2 + i * spacePerSegmentX,
					0,
					(-m_NumSegmentsZ * spacePerSegmentZ) / 2 + j * spacePerSegmentZ * m_NumSegmentsZ
				);

				m_Vertices.push_back(vertex);
				m_Indices.push_back(index);
				index++;
			}
		}

		for (uint32_t i = 0; i < numSegmentsZ; i++)
		{
			for (uint32_t j = 0; j < 2; j++)
			{
				vertex.pos = glm::vec3(
					(-m_NumSegmentsX * spacePerSegmentX) / 2 + j * spacePerSegmentX * m_NumSegmentsX,
					0,
					(-m_NumSegmentsZ * spacePerSegmentZ) / 2 + i * spacePerSegmentZ
				);

				m_Vertices.push_back(vertex);
				m_Indices.push_back(index);
				index++;
			}
		}
	}

	void GridMesh::createTestMesh()
	{
		Vertex vertex{};
		vertex.color = glm::vec3(1, 1, 1);
		vertex.texCoord = glm::vec2(0, 0);

		vertex.pos = glm::vec3(5, 0, 5);
		m_Vertices.push_back(vertex);

		vertex.pos = glm::vec3(5, 0, -5);
		m_Vertices.push_back(vertex);

		vertex.pos = glm::vec3(-5, 0, -5);
		m_Vertices.push_back(vertex);

		vertex.pos = glm::vec3(5, 0, -5);
		m_Vertices.push_back(vertex);

		m_Indices.push_back(0);
		m_Indices.push_back(1);
		m_Indices.push_back(2);

		m_Indices.push_back(0);
		m_Indices.push_back(2);
		m_Indices.push_back(3);
	}
}