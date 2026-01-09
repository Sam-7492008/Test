// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TSBaseCharacter.h"
#include "StateMachineOwner.h"
#include "TSPlayerCharacter.generated.h"

class UJumpState;
class UInAirState;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UStateMachineComponent;
class UIdleState;
class ULocomotionState;
class USprintState;

UCLASS(Blueprintable)
class TSCHARACTER_API ATSPlayerCharacter : public ATSBaseCharacter, public IStateMachineOwner
{
	GENERATED_BODY()

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsSprinting;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM", meta=(AllowPrivateAccess="true"))
	UStateMachineComponent* StateMachine;
	
	UPROPERTY()
	ULocomotionState* LocomotionState;
	
	UPROPERTY()
	UIdleState* IdleState;
	
	UPROPERTY()
	USprintState* SprintState;
	
	UPROPERTY()
	UJumpState* JumpState;
	
	UPROPERTY()
	UInAirState* InAirState;
	
#pragma region Input
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
#pragma endregion Input

	void Move(const FInputActionValue& Value);
	void StopMove(const FInputActionValue& Value);
	FVector2D MovementInput;
	
	void SprintOn(const FInputActionValue& Value);
	void SprintOff(const FInputActionValue& Value);
	
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	bool bIsTryingToJump = false;
	
protected:
	virtual void BeginPlay() override;

public:
	ATSPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	virtual FVector2D GetMovementInput() const override;
	
	virtual void StartMovement(float MoveSpeed) override;
	virtual void PerformJump() override;
	
	virtual bool IsGrounded() const override;
	virtual bool IsSprinting() const override;
	virtual bool IsJumping() const override;
	
	virtual UIdleState* GetIdleState() const override;
	virtual ULocomotionState* GetLocomotionState() const override;
	virtual USprintState* GetSprintState() const override;
};
