#include "GridEntityManagerComponent.h"

#include "GridComponent.h"
#include "GridEntityComponent.h"
#include "GridMovementComponent.h"
#include <Utils.h>

qbert::GridEntityManagerComponent::GridEntityManagerComponent(dae::GameObject& owner, qbert::GridComponent& grid) :
	ObjectComponent(owner), m_pGrid(&grid)
{}

std::vector<qbert::GridEntityComponent*> qbert::GridEntityManagerComponent::GetEntitiesAt(glm::ivec2 index) const
{
	auto result = std::vector<GridEntityComponent*>();
	if (m_pGrid->IsValidTileIndex(index))
	{
		for (auto it = m_pEntities.begin(); it != m_pEntities.end(); ++it)
		{
			if ((*it)->GetMovement()->GetCurrentTileIndex() == index) 
			{
				result.push_back(*it);
			}
		}
	}
	return result;
}

qbert::GridComponent* qbert::GridEntityManagerComponent::GetGridComponent() const
{
	return m_pGrid;
}

void qbert::GridEntityManagerComponent::RegisterEntity(GridEntityComponent* entity)
{
	if (std::find(m_pEntities.begin(), m_pEntities.end(),entity) != m_pEntities.end())
	{
		m_pEntities.push_back(entity);
	}
}

bool qbert::GridEntityManagerComponent::RequestMove(GridEntityComponent* entity, glm::ivec2 direction)
{
	const auto movementComponent = entity->GetMovement();
	const auto tileIndex = movementComponent->GetCurrentTileIndex();

	bool result{};

	if (!movementComponent->IsMoving())
	{
		if (auto target = tileIndex + direction; m_pGrid->IsValidTileIndex(target)) 
		{
			movementComponent->MoveBetweenTiles(tileIndex, target);
			result = true;
		}
		else 
		{
			LOGLN("Not a valid tile");
		}

	}
	return result;
}
