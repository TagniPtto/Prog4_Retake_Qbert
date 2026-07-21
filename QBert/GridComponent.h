#pragma once
#include "Components/ObjectComponent.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <cinttypes>
#include <string>
#include <nlohmann/json.hpp>

namespace qbert 
{
	class GridComponent final : public dae::ObjectComponent
	{
	private:
		const static int tilePixelSizeX = 32;
		const static int tilePixelSizeY = 32;

		int m_tileXCount{};
		int m_tileYCount{};

		int m_tileSize{};

		using GridEntity = std::pair<dae::GameObject*, int>;
		std::vector<GridEntity>			m_entities;
		std::vector<dae::GameObject*>	m_tiles;

	public:
		~GridComponent() = default;
		explicit GridComponent(dae::GameObject& owner, const std::string& path);

	private:
		dae::GameObject* GetTileObject(glm::ivec2 index);
		glm::vec2 GetTileWorldLocation(glm::ivec2 index);

		bool IsValidTileIndex(glm::ivec2 index);
		void CreateTiles(const nlohmann::json& data);
		void CreateTile(int x, int y);

	public: 
		void Update() override;
		void RenderUI() override;
		void LoadMap(const nlohmann::json& data);
		void AddEntity(dae::GameObject* entity);
	};
}
