// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TSBaseCharacter.h"
#include "StateMachineOwner.h"
#include "TSPlayerCharacter.generated.h"

class UFireModeData;
class UPlayerStatData;
class UPlayerStatsComponent;
struct FPlayerStats;
class UCombatComponent;
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UPlayerStatsComponent* PlayerStatsComponent;
	
	UPROPERTY(BlueprintReadOnly, Category="Animation", meta = (AllowPrivateAccess = "true"))
	float DashX = 0.f;
	
	UPROPERTY(BlueprintReadOnly, Category="Animation", meta = (AllowPrivateAccess = "true"))
	float DashY = 0.f;
	
#pragma region State Machine Variables
	
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
	
#pragma endregion State Machine Variables
	
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
	
	UPROPERTY(EditDefaultsOnly, Category="Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;
	
#pragma endregion Input

#pragma region Input Functions
	
	void Move(const FInputActionValue& Value);
	void StopMove(const FInputActionValue& Value);
	FVector2D MovementInput;
	
	void SprintOn(const FInputActionValue& Value);
	void SprintOff(const FInputActionValue& Value);
	bool bIsSprinting = false;
	
	void StartJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	bool bIsTryingToJump = false;
	
	void StartAiming(const FInputActionValue& Value);
	void StopAiming(const FInputActionValue& Value);
	bool bIsAiming = false;
	
	void StartDashing(const FInputActionValue& Value);
	void StopDashing(const FInputActionValue& Value);
	bool bIsDashing = false;
	
	void StartFire(const FInputActionValue& Value);
	void StopFire(const FInputActionValue& Value);
	bool bIsFiring = false;
	
#pragma endregion Input Functions
	
#pragma region Other Functions
	
	void InitializeStatMachine();
	
#pragma endregion Other Functions
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	ATSPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPlayerStatData* PlayerStatData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFireModeData* PrimaryFireMode;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFireModeData* SecondaryFireMode;
	
	//Use Input Functions
	virtual void UseJumpInput() override;
	virtual void UseDashInput() override;
	virtual void UseFireInput() override;
	
	virtual FVector2D GetMovementInput() const override;
	virtual FVector GetCurrentVelocity() const override;
	virtual void HandleMovement(float MoveSpeed) override;
	virtual void PerformJump() override;
	virtual void PerformDash(float DashStrength) override;
	virtual void StopDash() override;
	virtual void PerformFire() override;
	
	virtual void HandleAim() override;
	virtual void ShowCursor(bool Value) override;
	
	virtual bool IsGrounded() const override;
	virtual bool IsSprinting() const override;
	virtual bool IsJumping() const override;
	virtual bool IsAiming() const override;
	virtual bool IsDashing() const override;
	virtual bool IsFiring() const override;
};
