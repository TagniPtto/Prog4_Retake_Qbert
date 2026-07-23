#pragma once
#include "Components/ObjectComponent.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <cinttypes>
#include <string>
#include <nlohmann/json.hpp>

#include "GridEvents.h"

namespace qbert 
{

	class GridEntityManagerComponent;
	class GridComponent final : public dae::ObjectComponent
	{
		const static int tilePixelSizeX = 32;
		const static int tilePixelSizeY = 32;

		int m_tileXCount{};
		int m_tileYCount{};

		int m_tileSize{};

		std::vector<dae::GameObject*>	m_tiles;
		GridEntityManagerComponent* m_pEntityManager;
	public:
		dae::GameObject* GetTileObject(glm::ivec2 index)const;
		glm::vec3 GetTileWorldLocation(glm::ivec2 index)const;
		glm::ivec2 GetClosestValidTile(glm::ivec2 index)const;
		bool IsValidTileIndex(glm::ivec2 index) const;

		void CreateTiles(const nlohmann::json& data);
		void CreateTile(int x, int y);

	public:
		~GridComponent() = default;
		explicit GridComponent(dae::GameObject& owner, const std::string& path);

	public: 
		void Update() override;
	};
}
