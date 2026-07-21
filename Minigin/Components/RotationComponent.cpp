#include "RotationComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"
#include "TimeManager.h"

dae::RotationComponent::RotationComponent(GameObject& owner, float frequency):
	ObjectComponent(owner), m_frequency(frequency)
{
	
}
void dae::RotationComponent::Update()
{
	m_currentAngle += m_frequency * Time::Get().GetDeltaTime();
	GetOwner()->GetTransform()->SetLocalRotation(m_currentAngle);
}
