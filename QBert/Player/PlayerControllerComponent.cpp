#include "PlayerControllerComponent.h"
#include <GameObject.h>

#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <InputSystem/InputManager.h>
#include <InputSystem/InputTypes.h>


#include <InputSystem/IInputCommand.h>
#include <TimeManager.h>
#include <Utils.h>
#include "../Grid/GridEntityComponent.h"
namespace qbert 
{
	class GridEntityMoveCommand : public dae::IInputCommand 
	{
	private:
		GridEntityComponent* entityComponent{};
	public:
		explicit GridEntityMoveCommand(GridEntityComponent* entity) :
			entityComponent(entity)
		{}
		virtual ~GridEntityMoveCommand() = default;
		void Execute(dae::InputContext) override
		{
			entityComponent->RequestMove(glm::ivec2{1,0});
		}
	};
	class MoveCommand : public dae::IInputCommand {
	public:
		dae::GameObject* obj{};
		float speed{1000.0f};
	public:
		explicit MoveCommand(dae::GameObject* ob):
			obj(ob)
		{}
		virtual ~MoveCommand() = default;
		void Execute(dae::InputContext context) override
		{
			auto direction = std::get<glm::vec2>(context.value);
			direction.y *= -1.0f;
			direction = glm::normalize(direction);
			const auto deltaTime = dae::Time::Get().GetDeltaTime();
			obj->GetTransform()->Translate(glm::vec3{direction * deltaTime * speed , 0.0f});
		}

	};
	class MoveDirectionCommand : public MoveCommand {
	public:
		glm::vec2 direction;
	public:
		explicit MoveDirectionCommand(dae::GameObject* ob , glm::vec2 _direction) :
			MoveCommand(ob), direction(_direction)
		{

		}
		virtual ~MoveDirectionCommand() = default;
		void Execute(dae::InputContext context) override
		{
			context.value = direction * (float)std::get<bool>(context.value);
			MoveCommand::Execute(context);
		}

	};
}

qbert::PlayerControllerComponent::PlayerControllerComponent(dae::GameObject& pawn):
	ObjectComponent(pawn)
{



}

void qbert::PlayerControllerComponent::Move(glm::vec2)
{}

void qbert::PlayerControllerComponent::ChangeState(std::unique_ptr<IPlayerState> newState)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->OnExit(*this);
	}
	m_pCurrentState = std::move(newState);
	if (m_pCurrentState)
	{
		m_pCurrentState->OnEnter(*this);
	}
}

void qbert::PlayerControllerComponent::Update()
{
	if (m_pCurrentState) {
		auto nextState = m_pCurrentState->Update(*this);
		if (nextState) ChangeState(std::move(nextState));
	}
}

void qbert::PlayerControllerComponent::Start()
{
	if (m_pEntityComponent = GetOwner()->GetComponent<GridEntityComponent>(); !m_pEntityComponent) {
		LOGLN("No Entity Component Found on object");
	}

	auto& inputSystem = dae::ServiceLocator<dae::InputManager>::Get();
	auto moveCommand = std::make_shared<qbert::MoveCommand>(GetOwner());
	auto moveUpCommand = std::make_shared<qbert::MoveDirectionCommand>(GetOwner(), glm::vec2(0, 1));
	auto moveDownCommand = std::make_shared<qbert::MoveDirectionCommand>(GetOwner(), glm::vec2(0, -1));
	auto moveLeftCommand = std::make_shared<qbert::MoveDirectionCommand>(GetOwner(), glm::vec2(-1, 0));
	auto moveRightCommand = std::make_shared<qbert::MoveDirectionCommand>(GetOwner(), glm::vec2(1, 0));

	inputSystem.BindCommand(
		std::move(moveCommand),
		dae::InputValueType::Vector2,
		dae::GamepadInput::LeftThumb,
		0,
		dae::InputTriggerType::Held
	);
	inputSystem.BindCommand(
		std::move(moveUpCommand),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyW,
		dae::InputTriggerType::Held
	);
	inputSystem.BindCommand(
		std::move(moveDownCommand),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyS,
		dae::InputTriggerType::Held
	);
	inputSystem.BindCommand(
		std::move(moveLeftCommand),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyA,
		dae::InputTriggerType::Held
	);
	inputSystem.BindCommand(
		std::move(moveRightCommand),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::KeyD,
		dae::InputTriggerType::Held
	);
	auto gridEntityMoveCommand = std::make_shared<qbert::GridEntityMoveCommand>(m_pEntityComponent);
	inputSystem.BindCommand(
		std::move(gridEntityMoveCommand),
		dae::InputValueType::Boolean,
		dae::KeyboardInput::UpArrow,
		dae::InputTriggerType::Held);
}
