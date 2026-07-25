#pragma once
#include "ObjectComponent.h"
#include "../ResourceSystem/Texture2D.h"
#include <memory>


namespace dae
{
	struct Rect {
		float left;
		float top;
		float width;
		float height;
	};
	class RenderComponent : public ObjectComponent
	{
	private:
		std::shared_ptr<dae::Texture2D> m_texture;

		Rect m_srcRectangle{};
		Rect m_dstRectangle{};
	public:
		Rect GetSourceRectangle()const;
		Rect GetDesitionationRectangle()const;
		
		void SetSourceRectangle(float x , float y , float width, float height);
		void SetDestinationRectangle(float x , float y , float width, float height);
		void SetSourceRectangle(Rect src);
		void SetDestinationRectangle(Rect dst);

		RenderComponent(dae::GameObject& owner, const std::string& filename = "");

		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<dae::Texture2D> texture);
	};


}
