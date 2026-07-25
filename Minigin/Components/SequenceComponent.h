#pragma once

#include "RenderComponent.h"

namespace dae
{
	struct FrameSequenceDefinition 
	{
		Rect sourceRectangle = {};
		int rows{};
		int columns{};
		int sequenceStart{};
		int sequenceLength{};
	};
	struct FrameSequence 
	{
		FrameSequenceDefinition  definition{};
		int currentIndex{};
		Rect Get() const;
	};
	class SequenceComponent final : public ObjectComponent
	{
	private:
		FrameSequence m_sequence;
		RenderComponent* m_pRenderingComponent;
	public:
		explicit SequenceComponent(dae::GameObject& owner ,const FrameSequence& data);
		void Start() override;
		void SetFrame(int i);
	};
}