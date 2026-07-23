#include "GridMovementComponent.h"
#include "GridComponent.h"
#include "GridInteractionComponent.h"
#include <GameObject.h>

#include <TimeManager.h>

qbert::GridMovementComponent::GridMovementComponent(dae::GameObject& owner, GridComponent& grid):
	dae::ObjectComponent(owner),
    m_pGrid(&grid)
{}

glm::ivec2 qbert::GridMovementComponent::GetCurrentTileIndex() const
{
    return m_CurrentTile;
}

bool qbert::GridMovementComponent::IsMoving() const
{ 
    return m_IsMoving;
}


void qbert::GridMovementComponent::Start()
{
    m_pTransform = GetOwner()->GetTransform();
    SetPositionWithVisualOffset(m_pGrid->GetTileWorldLocation(m_CurrentTile));
}

void qbert::GridMovementComponent::Update()
{
    if (m_IsMoving)
    {
        m_Progress += dae::Time::Get().GetDeltaTime() * m_Speed;
        const auto tile1Pos = m_pGrid->GetTileWorldLocation(m_FromTile);
        const auto tile2Pos = m_pGrid->GetTileWorldLocation(m_ToTile);
        const auto newPosition = InterpolatePosition(tile1Pos, tile2Pos, m_Progress);
        SetPositionWithVisualOffset(newPosition);
        if (m_Progress > 1.0f) {
            m_IsMoving = false;
            m_CurrentTile = m_ToTile;
            SetPositionWithVisualOffset(m_pGrid->GetTileWorldLocation(m_CurrentTile));
            //TODO Let Tiles know its been entered and exited . maybe use events here

        }
    }
}

void qbert::GridMovementComponent::SetPositionWithVisualOffset(glm::vec3 tilePosition)
{
    tilePosition.x += 16;
    tilePosition.y -= 16;
    m_pTransform->SetLocalPosition(tilePosition);
}

void qbert::GridMovementComponent::SetTileIndex(glm::ivec2 pos)
{
    m_pGrid->IsValidTileIndex(pos);

}

void qbert::GridMovementComponent::MoveBetweenTiles(glm::ivec2 t1, glm::ivec2 t2)
{
    m_FromTile = t1;
    m_ToTile = t2;
    m_Progress = 0.0f;
    m_IsMoving = true;
}

glm::vec3 qbert::GridMovementComponent::InterpolatePosition(glm::vec3 p1, glm::vec3 p2 , float t)
{
    return p1 + (p2 - p1) * t;
}

