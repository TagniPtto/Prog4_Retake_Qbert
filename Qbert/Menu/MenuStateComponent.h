#pragma once

#include <Components/ObjectComponent.h>


namespace qbert {
	class MenuStateComponent : public dae::ObjectComponent {
		explicit MenuStateComponent(class dae::GameObject& owner);
	};
}
