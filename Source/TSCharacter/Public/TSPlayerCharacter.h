// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TSBaseCharacter.h"
#include "StateMachineOwner.h"
#include "TSPlayerCharacter.generated.h"

// Components
class UCameraComponent;
class USpringArmComponent;

// Input
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

// Finite State Machine
enum class EPlayerAnimState : uint8;
class UStateMachineComponent;
class UIdleState;
class ULocomotionState;
class USprintState;
class ULandState;
class UJumpState;
class UInAirState;
class UDashState;

UCLASS(Blueprintable)
class TSCHARACTER_API ATSPlayerCharacter : public ATSBaseCharacter, public IStateMachineOwner
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	APlayerController* MyPlayerController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsSprinting;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation", meta = (AllowPrivateAccess = "true"))
	EPlayerAnimState CurrentAnimState;
	
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
	
	UPROPERTY()
	ULandState* LandState;
	
	UPROPERTY()
	UDashState* DashState;
	
#pragma region Input
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;
	
#pragma endregion Input

	void Move(const FInputActionValue& Value);
	void StopMove(const FInputActionValue& Value);
	FVector2D MovementInput;
	
	void SprintOn(const FInputActionValue& Value);
	void SprintOff(const FInputActionValue& Value);
	
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	bool bIsTryingToJump = false;
	
	void StartAiming(const FInputActionValue& Value);
	void StopAiming(const FInputActionValue& Value);
	bool bIsAiming = false;
	
	void StartDashing(const FInputActionValue& Value);
	void StopDashing(const FInputActionValue& Value);
	bool bIsDashing = false;
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	ATSPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	//Use Input Functions
	virtual void UseJumpInput() override;
	virtual void UseDashInput() override;
	
	virtual FVector2D GetMovementInput() const override;
	virtual FVector GetCurrentVelocity() const override;
	virtual void HandleMovement(float MoveSpeed) override;
	virtual void PerformJump() override;
	virtual void PerformDash(float DashStrength) override;
	virtual void HandleAim() override;
	
	virtual bool IsGrounded() const override;
	virtual bool IsSprinting() const override;
	virtual bool IsJumping() const override;
	virtual bool IsAiming() const override;
	virtual bool IsDashing() const override;
};
