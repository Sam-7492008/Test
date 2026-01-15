// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "States/SuperState/AbilityState.h"
#include "DashState.generated.h"

UCLASS()
class FINITESTATEMACHINE_API UDashState : public UAbilityState
{
	GENERATED_BODY()
	
	
public:
	virtual void Enter(const FStateContext& StateContext) override;
	virtual void Update(const FStateContext& StateContext) override;
	virtual void Exit(const FStateContext& StateContext) override;
	
	float lastDashTime = 0.0f;
	bool CanDash() const;
	
private:
	float DashStartTime = 0.0f;
	float DashEndTime = 0.0f;
	
};
