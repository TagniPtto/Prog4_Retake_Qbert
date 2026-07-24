#include "GridEntityManagerComponent.h"

#include "GridComponent.h"
#include "GridEntityComponent.h"
#include "GridMovementComponent.h"
#include <Utils.h>

qbert::GridEntityManagerComponent::GridEntityManagerComponent(dae::GameObject& owner, qbert::GridComponent& grid) :
	ObjectComponent(owner), m_pGrid(&grid)
{}

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
