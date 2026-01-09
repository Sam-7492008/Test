// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TSBaseCharacter.generated.h"

UCLASS(Abstract)
class TSCHARACTER_API ATSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float WalkSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float SprintSpeed;

protected:
	virtual void BeginPlay() override;

public:
	ATSBaseCharacter();
	virtual void Tick(float DeltaTime) override;
};
