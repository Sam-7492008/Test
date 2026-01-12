// Fill out your copyright notice in the Description page of Project Settings.


#include "TSPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StateData.h"
#include "StateMachineComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "States/SubStates/DashState.h"

#include "States/SubStates/IdleState.h"
#include "States/SubStates/InAirState.h"
#include "States/SubStates/JumpState.h"
#include "States/SubStates/LandState.h"
#include "States/SubStates/LocomotionState.h"
#include "States/SubStates/SprintState.h"

ATSPlayerCharacter::ATSPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	StateMachine = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine"));
	StateMachine->PrimaryComponentTick.bCanEverTick = true;
}

#pragma region Input Functions

void ATSPlayerCharacter::Move(const FInputActionValue& Value)
{
	MovementInput = Value.Get<FVector2D>();
}

void ATSPlayerCharacter::StopMove(const FInputActionValue& Value)
{
	MovementInput = FVector2D::ZeroVector;
}

void ATSPlayerCharacter::SprintOn(const FInputActionValue& Value)
{
	bIsSprinting = true;
}

void ATSPlayerCharacter::SprintOff(const FInputActionValue& Value)
{
	bIsSprinting = false;
}

void ATSPlayerCharacter::StartJump(const FInputActionValue& Value)
{
	bIsTryingToJump = true;
}

void ATSPlayerCharacter::StopJump(const FInputActionValue& Value)
{
	bIsTryingToJump = false;
}

void ATSPlayerCharacter::StartAiming(const FInputActionValue& Value)
{
	bIsAiming = true;
}

void ATSPlayerCharacter::StopAiming(const FInputActionValue& Value)
{
	bIsAiming = false;
}

void ATSPlayerCharacter::StartDashing(const FInputActionValue& Value)
{
	bIsDashing = true;
}

void ATSPlayerCharacter::StopDashing(const FInputActionValue& Value)
{
	bIsDashing = false;
}

#pragma endregion Input Functions

void ATSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	StateMachine->InitializeOwner(TScriptInterface<IStateMachineOwner>(this));
	
	IdleState = NewObject<UIdleState>(StateMachine);
	IdleState->Initialize(StateMachine, EFSMStateTypes::Idle);
	
	LocomotionState = NewObject<ULocomotionState>(StateMachine);
	LocomotionState->Initialize(StateMachine, EFSMStateTypes::Locomotion);
	
	SprintState = NewObject<USprintState>(StateMachine);
	SprintState->Initialize(StateMachine, EFSMStateTypes::Sprint);
	
	JumpState = NewObject<UJumpState>(StateMachine);
	JumpState->Initialize(StateMachine, EFSMStateTypes::Jump);
	
	InAirState = NewObject<UInAirState>(StateMachine);
	InAirState->Initialize(StateMachine, EFSMStateTypes::InAir);
	
	LandState = NewObject<ULandState>(StateMachine);
	LandState->Initialize(StateMachine, EFSMStateTypes::Land);
	
	DashState = NewObject<UDashState>(StateMachine);
	DashState->Initialize(StateMachine, EFSMStateTypes::Dash);
	
	StateMachine->Initialize(LocomotionState);
	StateMachine->RegisterState(LocomotionState);
	StateMachine->RegisterState(SprintState);
	StateMachine->RegisterState(JumpState);
	StateMachine->RegisterState(InAirState);
	StateMachine->RegisterState(LandState);
	StateMachine->RegisterState(DashState);
}

void ATSPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	MyPlayerController = Cast<APlayerController>(NewController);
}

void ATSPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentAnimState = StateMachine->GetContext().AnimState;
}

void ATSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATSPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ATSPlayerCharacter::StopMove);
		
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ATSPlayerCharacter::SprintOn);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATSPlayerCharacter::SprintOff);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATSPlayerCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATSPlayerCharacter::StopJump);
		
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ATSPlayerCharacter::StartAiming);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ATSPlayerCharacter::StopAiming);
		
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ATSPlayerCharacter::StartDashing);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &ATSPlayerCharacter::StopDashing);
	}
}

void ATSPlayerCharacter::HandleMovement(float MoveSpeed)
{	
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementInput.Y);
	AddMovementInput(RightDirection, MovementInput.X);
}

void ATSPlayerCharacter::PerformJump()
{
	Jump();
}

void ATSPlayerCharacter::PerformDash(float DashStrength)
{
	FVector DashDirection(MovementInput.Y, MovementInput.X, 0);
	DashDirection.Normalize();
	
	GetCharacterMovement()->Velocity = DashDirection * DashStrength;
}

void ATSPlayerCharacter::HandleAim()
{
	if (!bIsAiming)
	{
		MyPlayerController->bShowMouseCursor = false;
		return;
	}
	
	MyPlayerController->bShowMouseCursor = true;
	
	FHitResult Hit;
	if (MyPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
	{
		FVector LookTarget = Hit.ImpactPoint;
		FVector AimDirection = LookTarget - GetActorLocation();
		AimDirection.Z = 0;
		
		FRotator Rotation = AimDirection.Rotation();
		SetActorRotation(Rotation);
	}
}

void ATSPlayerCharacter::UseJumpInput()
{
	bIsTryingToJump = false;
}

void ATSPlayerCharacter::UseDashInput()
{
	bIsDashing = false;
}

FVector2D ATSPlayerCharacter::GetMovementInput() const
{
	return MovementInput;
}

FVector ATSPlayerCharacter::GetCurrentVelocity() const
{
	return GetCharacterMovement()->Velocity;
}

bool ATSPlayerCharacter::IsGrounded() const
{
	return GetCharacterMovement()->IsMovingOnGround();
}

bool ATSPlayerCharacter::IsSprinting() const
{
	return bIsSprinting;
}

bool ATSPlayerCharacter::IsJumping() const
{
	return bIsTryingToJump;
}

bool ATSPlayerCharacter::IsAiming() const
{
	return bIsAiming;
}

bool ATSPlayerCharacter::IsDashing() const
{
	if (DashState->CanDash() && bIsDashing)
	{
		return true;
	}
	return false;
}

