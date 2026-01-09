// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States/SuperState/GroundedState.h"
#include "JumpState.generated.h"

UCLASS()
class FINITESTATEMACHINE_API UJumpState : public UGroundedState
{
	GENERATED_BODY()
	
protected:
	virtual void Enter(const FStateContext& StateContext) override;
	
};
