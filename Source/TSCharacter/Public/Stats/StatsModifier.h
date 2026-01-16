#pragma once

#include "StatsModifier.generated.h"

UENUM(BlueprintType)
enum class EPlayerStatsType : uint8
{
	MoveSpeed,
	DashSpeed,
	PrimaryDamage,
	PrimaryFireRate,
	PrimaryFireRange,
	SecondaryDamage,
	SecondaryFireRate,
	SecondaryFireRange
};

UENUM(BlueprintType)
enum class EModifierOp : uint8
{
	Additive,
	Multiplicative
};

USTRUCT(BlueprintType)
struct FStatsModifier
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString UpgradeName;
	
	UPROPERTY(EditAnywhere)
	FString Description;
	
	UPROPERTY(EditAnywhere)
	EPlayerStatsType StatType;
	
	UPROPERTY(EditAnywhere)
	EModifierOp Operation;
	
	UPROPERTY(EditAnywhere)
	float Value;
	
	UPROPERTY(EditAnywhere)
	int32 Priority = 0;
};
