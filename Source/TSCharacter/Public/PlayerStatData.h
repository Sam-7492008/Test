#pragma once

#include "Engine/DataAsset.h"
#include "PlayerStatData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed = 600.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SprintSpeed = 800.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DashStrength = 120000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DashDuration = 0.15f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int NumberOfDashes = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PrimaryAttackDamage = 20.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PrimaryFireRate = 1.15f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PrimaryFireRange = 2000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SecondaryAttackDamage = 40.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SecondaryFireRate = 1.15f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SecondaryFireRange = 2000.0f;
	
};

UCLASS(BlueprintType)
class UPlayerStatData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPlayerStats PlayerBaseStats;
	
};

