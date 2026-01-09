// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States/SuperState/GroundedState.h"
#include "IdleState.generated.h"

UCLASS()
class FINITESTATEMACHINE_API UIdleState : public UGroundedState
{
	GENERATED_BODY()
	
protected:
	virtual void Update(const FStateContext& StateContext) override;
};
