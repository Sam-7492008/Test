// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStatData.h"
#include "Components/ActorComponent.h"
#include "Stats/StatsModifier.h"
#include "PlayerStatsComponent.generated.h"


class UUpgradeStatsData;
class UPlayerStatData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSCHARACTER_API UPlayerStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerStatsComponent();
	
	void Initialize(const UPlayerStatData* PlayerStatData);
	void ApplyUpgrade(const UUpgradeStatsData* Upgrade);
	
	const FPlayerStats& GetPlayerStats() const;
	const FWeaponStats& GetPrimaryWeaponStats() const;
	const FWeaponStats& GetSecondaryWeaponStats() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void RecalculatePlayerStats();
	
private:
	UPROPERTY()
	const UPlayerStatData* BaseData = nullptr;
	
	UPROPERTY()
	TArray<FStatsModifier> Modifiers;
	
	UPROPERTY()
	TMap<const UUpgradeStatsData*, int32> AppliedUpgrades;
	
	FPlayerStats CachedPlayerStats;
	FWeaponStats CachedPrimaryWeaponStats;
	FWeaponStats CachedSecondaryWeaponStats;
};
