#include "AnimationComponent.h"
#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "../Utils.h"
#include "GameObject.h"
#include "TimeManager.h"

#include <iostream>



void dae::AnimationComponent::PauseCurrentAnimation()
{
	m_currentSequence->m_playing = false;
}

void dae::AnimationComponent::ResumeCurrentAnimation()
{
	m_currentSequence->m_playing = true;
}

void dae::AnimationComponent::AddAnimationSequence(const std::string& name, const AnimationSequence& animSeq)
{
	m_sequences.emplace(name,animSeq);
}

dae::AnimationSequence::AnimationSequence(const FrameSequence& sequence, float timePerFrame, AnimationPlayBack playback) :
	m_sequence(sequence),m_timePerFrame(timePerFrame), m_playback(playback)
{}

void dae::AnimationSequence::Update(float deltaTime)
{
	if (m_sequence.definition.sequenceLength <= 1 || !m_playing) 
	{
		return;
	}
	m_timer += deltaTime;
	if (m_timer >= m_timePerFrame) 
	{
		m_timer = 0.f;
		switch (m_playback) {
		case AnimationPlayBack::Normal: 
		{
			if (m_sequence.currentIndex == m_sequence.definition.sequenceLength - 1) return;
			++m_sequence.currentIndex;
		}
		break;
		case AnimationPlayBack::Reversed:
		{
			if (m_sequence.currentIndex == 0) return;
			--m_sequence.currentIndex;
		}
		break;
		case AnimationPlayBack::Looped:
		{
			m_sequence.currentIndex = MODULO(++m_sequence.currentIndex, m_sequence.definition.sequenceLength);
		}
		break;
		case AnimationPlayBack::ReverseLooped:
		{
			m_sequence.currentIndex = MODULO(--m_sequence.currentIndex, m_sequence.definition.sequenceLength);
		}
		break;
		}
	}
}

void dae::AnimationSequence::Reset()
{
	m_sequence.currentIndex = 0;
	m_timer = 0.f;
}

dae::Rect dae::AnimationSequence::Get() const
{
	return m_sequence.Get();
}



dae::AnimationComponent::AnimationComponent(dae::GameObject& owner):
	dae::ObjectComponent(owner), m_currentSequence(nullptr)
{}

dae::AnimationComponent::~AnimationComponent() = default;

void dae::AnimationComponent::Start()
{
	if (m_pRenderComponent = GetOwner()->GetComponent<RenderComponent>(); !m_pRenderComponent)
	{
		LOGLN("No rendering Component on this object");
	}
}

void dae::AnimationComponent::Update()
{
	if (m_currentSequence) 
	{
		float deltaTime = Time::Get().GetDeltaTime();
		m_currentSequence->Update(deltaTime);
		Rect srcRect = m_currentSequence->Get();
		m_pRenderComponent->SetSourceRectangle(srcRect.left, srcRect.top, srcRect.width, srcRect.height);
	}
}

void dae::AnimationComponent::PlayAnimation(const std::string& name)
{
	if (auto it = m_sequences.find(name); it != m_sequences.end()) 
	{
		m_currentSequence = &(it->second);
		ResumeCurrentAnimation();
	}
}

