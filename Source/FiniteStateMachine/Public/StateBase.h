// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "States/StateTypes.h"
#include "StateBase.generated.h"

struct FStateContext;
class UStateData;
class IStateMachineOwner;
class UStateMachineComponent;

UCLASS(Abstract)
class FINITESTATEMACHINE_API UStateBase : public UObject
{
	GENERATED_BODY()
	
public:

	void Initialize(UStateMachineComponent* StateMachine, EFSMStateTypes State);
	
	virtual void Enter();
	virtual void Exit();
	virtual void Update(const FStateContext& StateContext);
	
	EFSMStateTypes GetStateType() const { return _StateType; }
	
	UFUNCTION(BlueprintCallable)
	FString GetStateName();
	
protected:
	
	UPROPERTY()
	UStateMachineComponent* _StateMachine;
	
	UPROPERTY()
	const UStateData* StateData;
	
	EFSMStateTypes _StateType;
	
	bool isExitingState = false;
	bool isAnimationFinished = false;
	
};
