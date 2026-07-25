#include "SequenceComponent.h"
#include "../GameObject.h"
#include "../Utils.h"

dae::Rect dae::FrameSequence::Get() const
{
	int index = definition.sequenceStart + currentIndex;
	float rWidth = definition.sourceRectangle.width / definition.columns;
	float rHeight = definition.sourceRectangle.height / definition.rows;

	int indexX = index % definition.columns;
	int indexY = index / definition.columns;

	float rLeft = definition.sourceRectangle.left + indexX * rWidth;
	float rTop = definition.sourceRectangle.top + indexY * rHeight;

	Rect result
	{
		.left = rLeft,
		.top = rTop,
		.width = rWidth,
		.height = rHeight
	};
	return result;
}

dae::SequenceComponent::SequenceComponent(dae::GameObject& owner, const FrameSequence& data) :
	ObjectComponent(owner),m_sequence(data), m_pRenderingComponent()
{}

void dae::SequenceComponent::Start()
{
	if (m_pRenderingComponent = GetOwner()->GetComponent<RenderComponent>(); !m_pRenderingComponent) 
	{
		LOGLN("No rendering Component on this object");
	}
	SetFrame(0);
}


void dae::SequenceComponent::SetFrame(int i)
{
	int index = std::max(0,std::min(i, m_sequence.definition.sequenceLength));
	m_sequence.currentIndex = index;
	m_pRenderingComponent->SetSourceRectangle(m_sequence.Get());
}
