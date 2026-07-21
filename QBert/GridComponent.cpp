#include "GridComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <Components/RenderComponent.h>
#include <Components/AnimationComponent.h>
#include <Renderer.h>

#include <imgui.h>
#include <nlohmann/json.hpp>
#include <fstream>

#include <Utils.h>


bool qbert::GridComponent::IsValidTileIndex(glm::ivec2 index)
{
	return !(index.x >= m_tileXCount || index.x < 0 || index.y >= m_tileYCount || index.y < 0);
}




void qbert::GridComponent::Update()
{
}

void qbert::GridComponent::RenderUI()
{
	ImGui::Begin("GridObjectWindow");
	ImGui::End();
}


qbert::GridComponent::GridComponent(dae::GameObject& owner, const std::string& path):
	ObjectComponent(owner)
{
	std::ifstream file(path);
	if (file.is_open()) {
		auto data = nlohmann::json::parse(file);
		LoadMap(data);
	}
	else {
		LOGLN("Failed to open : " << path);
	}
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
void qbert::GridComponent::LoadMap(const nlohmann::json& data)
{

	m_tileSize = data["tileSize"];
	const auto tiles = data["tiles"];

	m_tileYCount = (int)tiles.size();
	m_tileXCount = (int)tiles[0].size(); 

	m_tiles		= std::vector<dae::GameObject*>(m_tileYCount * m_tileXCount);
	m_entities	= std::vector<dae::GameObject*>(m_tileYCount * m_tileXCount);
	CreateTiles(data);
}
