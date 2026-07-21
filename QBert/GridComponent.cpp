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
	GetOwner()->GetTransform()->Rotate(-1.0f);
	for (auto& obje : objects)
	{
		for (auto& obj : obje)
		{
			if (obj) {

			obj->GetTransform()->Rotate(1.0f);
			}
		}
	}
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
	const float xPos{ float(x * m_tileSize * tilePixelSizeY) };
	const float yPos{ float(y * m_tileSize * tilePixelSizeY) };

	auto obj = currentScene->CreateGameObject();
	obj->SetParent(GetOwner());
	obj->GetTransform()->SetLocalPosition(xPos,yPos);
	obj->GetTransform()->SetLocalRotation(-45.0f);

	const auto renderComp = obj->AddComponent<dae::RenderComponent>("Qbert Cubes.png");
	renderComp->SetSourceRectangle(0.0f,0.0f, tilePixelSizeX, tilePixelSizeY);
	renderComp->SetDestinationRectangle(0.0f, 0.0f, float(tilePixelSizeX * m_tileSize), float(tilePixelSizeY * m_tileSize));
	
	objects[y][x] = obj;
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

	objects = std::vector<std::vector<dae::GameObject*>>(m_tileYCount, std::vector<dae::GameObject*>(m_tileXCount));
	CreateTiles(data);
}
