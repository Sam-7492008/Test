// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "States/StateTypes.h"
#include "StateBase.generated.h"

class UStateData;
class IStateMachineOwner;
class UStateMachineComponent;
struct FStateContext;

UCLASS(Abstract)
class FINITESTATEMACHINE_API UStateBase : public UObject
{
	GENERATED_BODY()
	
public:

	void Initialize(UStateMachineComponent* StateMachine, EFSMStateTypes State);
	
	virtual void Enter(const FStateContext& StateContext);
	virtual void Exit(const FStateContext& StateContext);
	virtual void Update(const FStateContext& StateContext);
	
	virtual void OnAnimationTrigger(const FStateContext& StateContext);
	virtual void OnAnimationFinished(const FStateContext& StateContext);
	
	EFSMStateTypes GetStateType() const { return _StateType; }
	
	UFUNCTION(BlueprintCallable)
	FString GetStateName();
	
protected:
	
	UPROPERTY()
	float _StartTime;
	
	UPROPERTY()
	UStateMachineComponent* _StateMachine;
	
	UPROPERTY()
	const UStateData* StateData;
	
	EFSMStateTypes _StateType;
	
	bool bIsAnimationFinished = false;
	
};
