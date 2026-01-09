// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States/SuperState/AbilityState.h"
#include "InAirState.generated.h"

UCLASS()
class FINITESTATEMACHINE_API UInAirState : public UAbilityState
{
	GENERATED_BODY()
	
protected:
	virtual void Enter(const FStateContext& StateContext) override;
	virtual void Update(const FStateContext& StateContext) override;
};
