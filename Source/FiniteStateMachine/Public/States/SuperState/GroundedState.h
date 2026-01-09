// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "GroundedState.generated.h"

UCLASS(Abstract)
class FINITESTATEMACHINE_API UGroundedState : public UStateBase
{
	GENERATED_BODY()
	
protected:
	virtual void Update(const FStateContext& StateContext) override;
	
};
