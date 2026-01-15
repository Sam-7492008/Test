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
	CachedStats = BaseData->PlayerBaseStats;
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

const FPlayerStats& UPlayerStatsComponent::GetPlayerStat() const
{
	return CachedStats;
}

void UPlayerStatsComponent::RecalculatePlayerStats()
{
	CachedStats = BaseData->PlayerBaseStats;
	
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
		case EPlayerStatsType::MoveSpeed: Stat = &CachedStats.MoveSpeed; break;
		case EPlayerStatsType::DashSpeed: Stat = &CachedStats.DashStrength; break;
		case EPlayerStatsType::Damage: Stat = &CachedStats.PrimaryAttackDamage; break;
		case EPlayerStatsType::FireRate: Stat = &CachedStats.PrimaryFireRate; break;
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

