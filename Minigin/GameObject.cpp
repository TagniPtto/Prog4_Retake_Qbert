#include "GameObject.h"
#include "GameObject.h"
#include "GameObject.h"
#include <string>
#include <numbers>
#include "GameObject.h"
#include "Components/TransformComponent.h"
#include "ResourceSystem/ResourceManager.h"
#include "Renderer.h"



dae::GameObject::GameObject():m_transform(std::make_unique<dae::TransformComponent>(*this))
{
}

dae::GameObject::~GameObject()
{
	SetParent(nullptr);
	while (!m_children.empty())
	{
		m_children.back()->SetParent(nullptr);
	}
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_children.erase(
		std::remove(m_children.begin(), m_children.end(), child),
		m_children.end()
	);
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child);
}

bool dae::GameObject::IsChildOf(GameObject* potentialParent)
{
	if (potentialParent == nullptr)
		return false;
	if (m_parent == potentialParent)
		return true;
	return false;
}


void dae::GameObject::Start()
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Start();
	}
}

void dae::GameObject::Update()
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Update();
	}
	RemoveMarkedComponents();
}

void dae::GameObject::Render() const
{
	for (int i{}; i < (int)m_components.size(); i++) {
		m_components[i]->Render();
	}
}


dae::GameObject* dae::GameObject::GetParent() const
{
	return m_parent;
}

void dae::GameObject::SetParent(GameObject* newParent , bool keepWorldPosition)
{
	if (m_parent == newParent|| IsChildOf(newParent) || (newParent && newParent->IsChildOf(this)))
		return;

	if (m_parent == nullptr) {
		m_transform->SetLocalPosition(m_transform->GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
			m_transform->SetLocalPosition(m_transform->GetWorldPosition() - m_parent->GetTransform()->GetWorldPosition());
		m_transform->SetTransformDirty();
	}

	if (m_parent) m_parent->RemoveChild(this);
	m_parent = newParent;
	if (newParent) newParent->AddChild(this);
}

dae::GameObject* dae::GameObject::GetChild(int index) const
{
	dae::GameObject* child = nullptr;
	if ( 0 <= index && index < (int)m_children.size()) {
		child = m_children.at(index);
	}
	return child;
}

int dae::GameObject::GetChildCount() const
{
	return (int)m_children.size();
}

dae::TransformComponent* dae::GameObject::GetTransform()
{
	return m_transform.get();
}

void dae::GameObject::RemoveMarkedComponents()
{
	m_components.erase(
		std::remove_if(
			m_components.begin(),
			m_components.end(),
			[](const auto& ptr) { return ptr->IsMarkedForDestruction(); }
		),
		m_components.end()
	);
}


void dae::GameObject::MarkForDestruction()
{
	m_markedForDestruction = true;
	for (auto& comp: m_components) {
		comp->MarkForDestruction();
	}
}

bool dae::GameObject::IsMarkedForDestruction() const
{
	return m_markedForDestruction;
}