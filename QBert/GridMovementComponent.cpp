#include "GridMovementComponent.h"
#include "GridComponent.h"
#include <GameObject.h>

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>
#include <TimeManager.h>

qbert::GridMovementComponent::GridMovementComponent(dae::GameObject& owner, dae::TransformComponent* trans, GridComponent* grid):
	dae::ObjectComponent(owner),
    m_pGridComp(grid),
    m_pTransformComp(trans) 
{
    if (!m_pTransformComp) {
        m_pTransformComp = GetOwner()->GetTransform();
    }
    dae::Scene* scene = dae::ServiceLocator<dae::SceneManager>::Get().GetActiveScene();
    if (!m_pGridComp) {
        m_pGridComp = scene->FindComponent<qbert::GridComponent>();
    }
    if (m_pGridComp && m_pTransformComp) {
        glm::ivec2 posId = m_pGridComp->GetClosestAvailableTile(m_pTransformComp->GetWorldPosition());
        auto tilePos = m_pGridComp->GetTilePosition(posId);
        m_pTransformComp->SetLocalPosition(tilePos);
    }
}

bool qbert::GridMovementComponent::IsMoving()
{
    return m_IsMoving;
}

bool qbert::GridMovementComponent::RequestMove( glm::ivec2 direction)
{
    if (m_IsMoving)
        return false;

    glm::ivec2 target = m_CurrentTile + direction;

    if (m_pGridComp->IsTileOccupiedByBlock(target))
        return false;

    m_FromTile= m_CurrentTile;
    m_ToTile = target;

    m_Progress = 0.f;
    m_IsMoving = true;

    return true;
}

void qbert::GridMovementComponent::Update()
{
    if (!m_IsMoving)
        return;

    m_Progress += m_Speed * dae::Time::Get().GetDeltaTime();

    auto fromPosition = m_pGridComp->GetTilePosition(m_FromTile);
    auto toPosition = m_pGridComp->GetTilePosition(m_ToTile);

    if (m_Progress >= 1.0f)
    {
        m_Progress = 1.0f;
        m_IsMoving = false;
        m_CurrentTile = m_ToTile;
    }

    auto position = glm::mix(fromPosition, toPosition, m_Progress);
    m_pTransformComp->SetLocalPosition(position);
}
void qbert::GridMovementComponent::Deserialize(const nlohmann::json &)
{}

void qbert::GridMovementComponent::Serialize(nlohmann::json &) const
{}
