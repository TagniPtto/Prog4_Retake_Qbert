#include "ObjectComponent.h"
#include "ObjectComponent.h"
#include "ObjectComponent.h"
#include "ObjectComponent.h"
#include "GameObject.h"


dae::ObjectComponent::ObjectComponent(dae::GameObject& owner) : m_owner(&owner)
{}

dae::GameObject* dae::ObjectComponent::GetOwner() const
{
	return m_owner;
}

void dae::ObjectComponent::Render() const
{}

void dae::ObjectComponent::Start()
{}

void dae::ObjectComponent::Update()
{}

void dae::ObjectComponent::FixedUpdate(float)
{}

void dae::ObjectComponent::MarkForDestruction()
{
	m_markedForDestruction = true;
}

bool dae::ObjectComponent::IsMarkedForDestruction() const
{
	return m_markedForDestruction;
}