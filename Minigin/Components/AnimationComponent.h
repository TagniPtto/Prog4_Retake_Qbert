#pragma once

#include "SequenceComponent.h"
#include <unordered_map>
#include <string>

namespace dae 
{	
	class AnimationSequence final
	{
	public:
		enum struct AnimationPlayBack {
			Normal,
			Looped,
			Reversed,
			ReverseLooped,
		};
	public:
		explicit AnimationSequence(const FrameSequence& sequence , float timePerFrame, AnimationPlayBack playback = AnimationPlayBack::Normal);
		void Update(float deltaTime);
		void Reset();
		Rect Get() const;

	private:
		FrameSequence m_sequence;

		AnimationPlayBack m_playback = AnimationPlayBack::Normal;
		float m_timer = 0;
		float m_timePerFrame = 0;

	public:
		bool m_playing = true;
	};


	class AnimationComponent final : public ObjectComponent 
	{
	public:
		explicit AnimationComponent(dae::GameObject& owner);
		~AnimationComponent();
	public:
		void Start() override;
		void Update() override;

		void AddAnimationSequence(const std::string& name,const AnimationSequence& animSeq);
		void PlayAnimation(const std::string& name);

		void PauseCurrentAnimation();
		void ResumeCurrentAnimation();

	private:
		std::unordered_map<std::string,AnimationSequence> m_sequences;
		AnimationSequence* m_currentSequence;
		RenderComponent* m_pRenderComponent{};
	};

}