#pragma once
#include <Components/ObjectComponent.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <cinttypes>
#include <string>
#include <nlohmann/json.hpp>

#include "GridEvents.h"
#include "Tiles/ITileComponent.h"

namespace qbert 
{

	class GridComponent final : public dae::ObjectComponent
	{
		const static int tilePixelSizeX = 32;
		const static int tilePixelSizeY = 32;

		int m_tileXCount{};
		int m_tileYCount{};

		int m_tileSize{};

		std::vector<ITileComponent*> m_tiles;
		std::vector<std::vector<int>> m_tileInfo;
	public:
		ITileComponent* GetTile(glm::ivec2 index)const;
		glm::vec3 GetTileWorldLocation(glm::ivec2 index)const;
		glm::ivec2 GetClosestValidTile(glm::ivec2 index)const;
		bool IsValidTileIndex(glm::ivec2 index) const;

		void CreateTiles();
		void CreateTile(int x, int y);
		dae::GameObject* CreateEmpty(int x, int y);

	public:
		~GridComponent() = default;
		explicit GridComponent(dae::GameObject& owner, const std::string& path);
	};
}
