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
	
	// State: Locomotion
	virtual FVector2D GetMovementInput() const = 0;
	
	virtual void StartMovement(float MoveSpeed) {}
	virtual void PerformJump() {}
	
	virtual bool IsGrounded() const = 0;
	virtual bool IsSprinting() const = 0;
	virtual bool IsJumping() const = 0;
	
	virtual UIdleState* GetIdleState() const = 0;
	virtual ULocomotionState* GetLocomotionState() const = 0;
	virtual USprintState* GetSprintState() const = 0;
	
};
