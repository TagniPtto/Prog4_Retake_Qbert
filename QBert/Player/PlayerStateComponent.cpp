#include "PlayerStateComponent.h"
#include <GameObject.h>
#include <Components/AnimationComponent.h>

#include "../GridMovementComponent.h"
#include "../GridInteractionComponent.h"


qbert::PlayerStateComponent::PlayerStateComponent(
	dae::GameObject& owner, 
	dae::AnimationComponent* anim, 
	qbert::GridMovementComponent* mov,
	qbert::GridInteractionComponent* in):
	ObjectComponent(owner),
	m_pAnimComp(anim),
	m_pMovementComp(mov),
	m_pInteractionComp(in)
	
{
	if (!m_pAnimComp) {
		m_pAnimComp = GetOwner()->GetComponent<dae::AnimationComponent>();
	}
	if (!m_pMovementComp) {
		m_pMovementComp = GetOwner()->GetComponent<GridMovementComponent>();
	}
	if (!m_pInteractionComp) {
		m_pInteractionComp = GetOwner()->GetComponent<GridInteractionComponent>();
	}
	m_pCurrentState = std::make_unique<qbert::IdleState>();
}

void qbert::PlayerStateComponent::ChangeState(std::unique_ptr<PlayerState> newState)
{
	if (m_pCurrentState) 
	{
		m_pCurrentState->OnExit(*this);
	}
	m_pCurrentState = std::move(newState);
	if (m_pCurrentState)
	{
		m_pCurrentState->OnEnter(*this);
	}
}

void qbert::PlayerStateComponent::HandleRequest(PlayerStateChange change)
{
	if (m_pCurrentState) {
		auto nextState = m_pCurrentState->HandleRequest(*this, change);
		if (nextState) ChangeState(std::move(nextState));
	}
}

void qbert::PlayerStateComponent::Update()
{
	if (m_pCurrentState) {
		auto nextState = m_pCurrentState->Update(*this);
		if (nextState) ChangeState(std::move(nextState));
	}
}

dae::AnimationComponent* qbert::PlayerStateComponent::GetAnimationComponent() const
{
	return m_pAnimComp;
}

qbert::GridMovementComponent* qbert::PlayerStateComponent::GetGridMovementComponent() const
{
	return m_pMovementComp;
}

qbert::GridInteractionComponent* qbert::PlayerStateComponent::GetGridInterationComponent() const
{
	return m_pInteractionComp;
}



void qbert::PlayerStateComponent::Deserialize(const nlohmann::json&)
{}

void qbert::PlayerStateComponent::Serialize(nlohmann::json&) const
{}