#pragma once
#include <memory>
#include <InputSystem/InputTypes.h>
namespace qbert
{
	class PlayerControllerComponent;

	class IPlayerState {
	public:
		virtual ~IPlayerState() = default;

		virtual void OnEnter(PlayerControllerComponent& stateComponent);
		virtual void OnExit(PlayerControllerComponent& stateComponent);

		virtual std::unique_ptr<IPlayerState> Update(PlayerControllerComponent& stateComponent);
		virtual std::unique_ptr<IPlayerState> HandleRequest(PlayerControllerComponent&) = 0;
	};


	class IdleState : public IPlayerState {
	public:
		virtual ~IdleState() = default;
		virtual void OnEnter(PlayerControllerComponent& stateComponent) override;
		virtual std::unique_ptr<IPlayerState> HandleRequest(PlayerControllerComponent&) override;
	};


	class MoveState : public IPlayerState {
	public:
		virtual ~MoveState() = default;
		virtual void OnEnter(PlayerControllerComponent& stateComponent) override;
		virtual std::unique_ptr<IPlayerState> Update(PlayerControllerComponent& stateComponent) override;
		virtual std::unique_ptr<IPlayerState> HandleRequest(PlayerControllerComponent&) override;
	};

	class DeadState : public IPlayerState {
	public:
		virtual ~DeadState() = default;
		virtual void OnEnter(PlayerControllerComponent& stateComponent) override;
		virtual std::unique_ptr<IPlayerState> HandleRequest(PlayerControllerComponent&) override;
	};
}