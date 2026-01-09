// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States/SuperState/GroundedState.h"
#include "LocomotionState.generated.h"

UCLASS()
class FINITESTATEMACHINE_API ULocomotionState : public UGroundedState
{
	GENERATED_BODY()
	
protected:
	virtual void Enter() override;
	virtual void Update(const FStateContext& StateContext) override;
	
};
