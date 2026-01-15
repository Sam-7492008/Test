#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StateMachineOwner.generated.h"

class UIdleState;
class ULocomotionState;
class USprintState;

UINTERFACE(MinimalAPI)
class UStateMachineOwner : public UInterface
{
	GENERATED_BODY()
};

class FINITESTATEMACHINE_API IStateMachineOwner
{
	GENERATED_BODY()

public:
	
	//Use Input Functions
	virtual void UseJumpInput() {}
	virtual void UseDashInput() {}
	virtual void UseFireInput() {}
	
	virtual FVector2D GetMovementInput() const = 0;
	virtual FVector GetCurrentVelocity() const = 0;
	virtual void HandleMovement(float MoveSpeed) {}
	virtual void PerformJump() {}
	virtual void PerformDash(float DashStrength) {}
	virtual void StopDash() {}
	virtual void PerformFire() {}
	
	virtual void HandleAim() {}
	virtual void ShowCursor(bool Value) {}
	
	virtual bool IsGrounded() const = 0;
	virtual bool IsSprinting() const = 0;
	virtual bool IsJumping() const = 0;
	virtual bool IsAiming() const = 0;
	virtual bool IsDashing() const = 0;
	virtual bool IsFiring() const = 0;
	
};
