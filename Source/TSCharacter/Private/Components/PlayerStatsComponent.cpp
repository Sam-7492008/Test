#include "Components/PlayerStatsComponent.h"

#include "Stats/UpgradeStatsData.h"


UPlayerStatsComponent::UPlayerStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerStatsComponent::Initialize(const UPlayerStatData* PlayerStatData)
{
	BaseData = PlayerStatData;
	CachedPlayerStats = BaseData->PlayerBaseStats;
	CachedPrimaryWeaponStats = BaseData->PrimaryWeaponStat;
	CachedSecondaryWeaponStats = BaseData->SecondaryWeaponStat;
}

void UPlayerStatsComponent::ApplyUpgrade(const UUpgradeStatsData* Upgrade)
{
	if (!Upgrade) return;
	
	int32& Stacks = AppliedUpgrades.FindOrAdd(Upgrade);
	
	if (!Upgrade->bIsStackable && Stacks > 0) return;
	if (Stacks >= Upgrade->MaxStackSize) return;
	
	Modifiers.Add(Upgrade->Modifier);
	Stacks++;
	
	RecalculatePlayerStats();
}

const FPlayerStats& UPlayerStatsComponent::GetPlayerStats() const
{
	return CachedPlayerStats;
}

const FWeaponStats& UPlayerStatsComponent::GetPrimaryWeaponStats() const
{
	return CachedPrimaryWeaponStats;
}

const FWeaponStats& UPlayerStatsComponent::GetSecondaryWeaponStats() const
{
	return CachedSecondaryWeaponStats;
}

void UPlayerStatsComponent::RecalculatePlayerStats()
{
	CachedPlayerStats = BaseData->PlayerBaseStats;
	
	Modifiers.Sort(
		[](const FStatsModifier& A, const FStatsModifier& B)
		{
			return A.Priority < B.Priority;
		});
	
	for (const FStatsModifier& Modifier : Modifiers)
	{
		float* Stat = nullptr;
		
		switch (Modifier.StatType)
		{
		case EPlayerStatsType::MoveSpeed: Stat = &CachedPlayerStats.MoveSpeed; break;
		case EPlayerStatsType::DashSpeed: Stat = &CachedPlayerStats.DashStrength; break;
		case EPlayerStatsType::PrimaryDamage: Stat = &CachedPrimaryWeaponStats.BaseDamage; break;
		case EPlayerStatsType::PrimaryFireRate: Stat = &CachedPrimaryWeaponStats.BaseFireRate; break;
		case EPlayerStatsType::PrimaryFireRange: Stat = &CachedPrimaryWeaponStats.BaseFireRange; break;
		case EPlayerStatsType::SecondaryDamage: Stat = &CachedSecondaryWeaponStats.BaseDamage; break;
		case EPlayerStatsType::SecondaryFireRate: Stat = &CachedSecondaryWeaponStats.BaseFireRate; break;
		case EPlayerStatsType::SecondaryFireRange: Stat = &CachedSecondaryWeaponStats.BaseFireRange; break;
		}
		
		if (!Stat) continue;
		
		if (Modifier.Operation == EModifierOp::Additive)
		{
			*Stat += Modifier.Value;
		}
		else
		{
			*Stat *= Modifier.Value;
		}
		
	}
	
}

