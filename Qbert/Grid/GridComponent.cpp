#include "GridComponent.h"

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <Components/RenderComponent.h>
#include <Components/AnimationComponent.h>
#include <ResourceSystem/ResourceManager.h>
#include <imgui.h>
#include <nlohmann/json.hpp>
#include <fstream>

#include <Utils.h>

#include "GridEntityManagerComponent.h"
#include "Tiles/GridVoidComponent.h"
#include "Tiles/GridTileComponent.h"
#include "Tiles/GridFloatingDiscComponent.h"


qbert::ITileComponent* qbert::GridComponent::GetTile(glm::ivec2 index) const
{
	qbert::ITileComponent* result{ nullptr };
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
	if (auto tile = GetTile(index); tile) {
		result = tile->GetOwner()->GetTransform()->GetWorldPosition();
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


void qbert::GridComponent::CreateTile(int x , int y)
{
	auto emptyObj = CreateEmpty(x,y);
	ITileComponent* tileComponent{};

	switch (m_tileInfo[x][y])
	{
	case 0: 
	{
		tileComponent = emptyObj->AddComponent<GridVoidComponent>();
	}
	break;
	case 1:
	{
		const auto renderComp = emptyObj->AddComponent<dae::RenderComponent>("Qbert Cubes.png");
		
		dae::FrameSequence fs{};
		fs.definition.columns = 1;
		fs.definition.rows = 3;
		fs.definition.sequenceLength = 3;
		fs.definition.sequenceStart = 0;
		fs.definition.sourceRectangle = { tilePixelSizeX, 0.0f, tilePixelSizeX, tilePixelSizeY*3 };

		emptyObj->AddComponent<dae::SequenceComponent>(fs);
		renderComp->SetDestinationRectangle(0.0f, 0.0f, float(tilePixelSizeX * m_tileSize), float(tilePixelSizeY * m_tileSize));
		tileComponent = emptyObj->AddComponent<GridTileComponent>();
	}break;
	case 2:
	{
		tileComponent = emptyObj->AddComponent<GridFloatingDiscComponent>();
	}break;

	default:
		LOGLN("Tile Type Not supported");
		break;
	}
	m_tiles[y*m_tileXCount + x] = tileComponent;
}

dae::GameObject* qbert::GridComponent::CreateEmpty(int x, int y)
{
	dae::Scene* currentScene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
	if (!currentScene) return nullptr;
	constexpr float xOffset{ tilePixelSizeX * 0.5f };
	constexpr float yOffset{ tilePixelSizeY * 0.75f };
	const float xPos{ float(x * m_tileSize * xOffset - y * m_tileSize * xOffset) };
	const float yPos{ float(x * m_tileSize * yOffset + y * m_tileSize * yOffset) };

	auto obj = currentScene->CreateGameObject();
	obj->SetParent(GetOwner());
	obj->GetTransform()->SetLocalPosition(xPos, yPos);
	return obj;
}

void qbert::GridComponent::CreateTiles()
{
	for (int y = 0; y < m_tileYCount; y++)
	{
		for (int x = 0; x < m_tileXCount; x++)
		{
			CreateTile(x, y);
		}
	}
}

qbert::GridComponent::GridComponent(dae::GameObject& owner, const std::string& path):
	ObjectComponent(owner)
{
	const auto data = dae::ServiceLocator<dae::ResourceManager>::Get().LoadMap(path);
	if (data.empty()) {

	}
	m_tileSize = data["tileSize"];
	m_tileInfo = data["tiles"].get<std::vector<std::vector<int>>>();;

	m_tileYCount = (int)m_tileInfo.size();
	m_tileXCount = (int)m_tileInfo[0].size();

	m_tiles = std::vector<qbert::ITileComponent*>(m_tileYCount * m_tileXCount);

	CreateTiles();
}
