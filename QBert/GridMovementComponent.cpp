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
}

bool qbert::GridMovementComponent::IsMoving()
{
    return m_IsMoving;
}


void qbert::GridMovementComponent::Update()
{
}