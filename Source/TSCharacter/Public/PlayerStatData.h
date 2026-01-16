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
	
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDamage = 20.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseFireRate = 1.15f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseFireRange = 2000.0f;
	
};

UCLASS(BlueprintType)
class UPlayerStatData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPlayerStats PlayerBaseStats;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponStats PrimaryWeaponStat;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponStats SecondaryWeaponStat;
	
};

