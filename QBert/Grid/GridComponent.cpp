#include "GridComponent.h"

#include <ServiceLocator.h>
#include <EventSystem/EventQueue.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <Components/RenderComponent.h>
#include <Components/AnimationComponent.h>
#include <Renderer.h>
#include "GridEntityManagerComponent.h"

#include <imgui.h>
#include <nlohmann/json.hpp>
#include <fstream>

#include <Utils.h>


dae::GameObject* qbert::GridComponent::GetTileObject(glm::ivec2 index) const
{
	dae::GameObject* result{ nullptr };
	if (IsValidTileIndex(index)) 
	{
		result = m_tiles[index.x + index.y * m_tileXCount];
	}
	else {
		LOGLN("Invalid TileIndex");
	}
	return result;
}

glm::vec3 qbert::GridComponent::GetTileWorldLocation(glm::ivec2 index)const
{
	glm::vec3 result{};
	if (auto tile = GetTileObject(index); tile) {
		result = tile->GetTransform()->GetWorldPosition();
	}
	return result;
}

glm::ivec2 qbert::GridComponent::GetClosestValidTile(glm::ivec2) const
{
	LOGLN("Not implemented yet returning unprocessed index");
	return glm::ivec2();
}

bool qbert::GridComponent::IsValidTileIndex(glm::ivec2 index) const
{
	return !(index.x >= m_tileXCount || index.x < 0 || index.y >= m_tileYCount || index.y < 0);
}




void qbert::GridComponent::Update()
{


}

void qbert::GridComponent::CreateTile(int x , int y)
{
	dae::Scene* currentScene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
	if (!currentScene) return;

	constexpr float xOffset{ tilePixelSizeX * 0.5f};
	constexpr float yOffset{ tilePixelSizeY * 0.75f};
	const float xPos{ float(x * m_tileSize * xOffset - y * m_tileSize * xOffset) };
	const float yPos{ float(x * m_tileSize * yOffset + y * m_tileSize * yOffset) };

	auto obj = currentScene->CreateGameObject();
	obj->SetParent(GetOwner());
	obj->GetTransform()->SetLocalPosition(xPos,yPos);

	const auto renderComp = obj->AddComponent<dae::RenderComponent>("Qbert Cubes.png");
	renderComp->SetSourceRectangle(0.0f,0.0f, tilePixelSizeX, tilePixelSizeY);
	renderComp->SetDestinationRectangle(0.0f, 0.0f, float(tilePixelSizeX * m_tileSize), float(tilePixelSizeY * m_tileSize));
	
	m_tiles[y*m_tileXCount + x] = obj;
}

void qbert::GridComponent::CreateTiles(const nlohmann::json& data)
{
	const auto tiles = data["tiles"];

	for (int y = 0; y < m_tileYCount; y++)
	{
		for (int x = 0; x < m_tileXCount; x++)
		{
			if (tiles[y][x] == 1)
			{
				CreateTile(x,y);
			}
		}
	}
}

qbert::GridComponent::GridComponent(dae::GameObject& owner, const std::string& path):
	ObjectComponent(owner)
{

	std::ifstream file(path);
	if (!file.is_open()) 
	{
		LOGLN("Failed to open : " << path);
		return;
	}
	auto data = nlohmann::json::parse(file);

	m_tileSize = data["tileSize"];
	const auto tiles = data["tiles"];

	m_tileYCount = (int)tiles.size();
	m_tileXCount = (int)tiles[0].size();

	m_tiles = std::vector<dae::GameObject*>(m_tileYCount * m_tileXCount);
	CreateTiles(data);
}
