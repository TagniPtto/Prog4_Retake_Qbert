#include "GridMovementComponent.h"
#include "GridComponent.h"
#include <GameObject.h>

#include <TimeManager.h>

qbert::GridMovementComponent::GridMovementComponent(dae::GameObject& owner, GridComponent& grid):
	dae::ObjectComponent(owner),
    m_pGrid(&grid)
{}

bool qbert::GridMovementComponent::IsMoving() const
{ 
    return m_IsMoving;
}


void qbert::GridMovementComponent::Update()
{
}

void qbert::GridMovementComponent::SetToTile(glm::ivec2 pos)
{
    m_pGrid->IsValidTileIndex(pos);
    auto newPosition = m_pGrid->GetTileWorldLocation({});
    newPosition.x += 8;
    newPosition.y += 8;
    GetOwner()->GetTransform()->SetLocalPosition(newPosition);
}

glm::vec2 qbert::GridMovementComponent::InterpolatePosition(glm::vec2 p1, glm::vec2 p2 , float t)
{
    return p1 + (p2 - p1) * t;
}

