// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States/SuperState/GroundedState.h"
#include "LandState.generated.h"

UCLASS()
class FINITESTATEMACHINE_API ULandState : public UGroundedState
{
	GENERATED_BODY()
	
protected:
	virtual void Enter(const FStateContext& StateContext) override;
};
