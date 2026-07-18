#include "PlayerControllerComponent.h"
#include "PlayerStateComponent.h"

#include <ServiceLocator.h>
#include <InputSystem/InputManager.h>
#include <InputSystem/InputTypes.h>


#include "PlayerCommands.h"


qbert::PlayerControllerComponent::PlayerControllerComponent(dae::GameObject& pawn):
	ObjectComponent(pawn)
{
	auto pStateComp = GetOwner()->GetComponent<qbert::PlayerStateComponent>();
	auto cMU = std::make_unique<qbert::PlayerStateRequestCommand>(pStateComp,PlayerStateChange::MoveUp);
	auto cMD = std::make_unique<qbert::PlayerStateRequestCommand>(pStateComp,PlayerStateChange::MoveDown);
	auto cML = std::make_unique<qbert::PlayerStateRequestCommand>(pStateComp,PlayerStateChange::MoveLeft);
	auto cMR = std::make_unique<qbert::PlayerStateRequestCommand>(pStateComp,PlayerStateChange::MoveRight);
	auto cM = std::make_unique<qbert::PlayerStateRequestCommand>(pStateComp,PlayerStateChange::MoveUp);

	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(cM),
		0,
		dae::InputValueType::Vector2,
		dae::GamepadInput::LeftThumb,
		dae::InputTriggerType::Held);

	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(cMU),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyW,
		dae::InputTriggerType::Pressed);
	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(cMD),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyS,
		dae::InputTriggerType::Pressed);
	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(cML),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyA,
		dae::InputTriggerType::Pressed);
	dae::ServiceLocator<dae::InputManager>::Get().BindCommand(
		std::move(cMR),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyD,
		dae::InputTriggerType::Pressed);
}


void qbert::PlayerControllerComponent::Deserialize(const nlohmann::json&)
{
	//auto commandBindings = data["CommandBindings"];

	//for (auto& commandBinding : commandBindings) {
	//	auto& binding = commandBinding["Binding"];
	//	auto& command = commandBinding["Command"];
	//	
	//}
}

void qbert::PlayerControllerComponent::Serialize(nlohmann::json &) const
{}
