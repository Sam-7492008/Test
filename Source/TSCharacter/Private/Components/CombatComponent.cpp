#include "Components/CombatComponent.h"

#include "PlayerStatData.h"
#include "Components/PlayerStatsComponent.h"
#include "Data/FireModeData.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::FireHitscan(FName SocketName, float Damage, float Range)
{
	if (!PlayerSkeletalMeshComp || !PlayerSkeletalMeshComp->DoesSocketExist(SocketName))
		return;

	constexpr float MinAimDistance = 150.0f;
	
	FVector PlayerLoc = GetOwner()->GetActorLocation();
	FVector ToTarget = AimTarget - PlayerLoc;
	ToTarget.Z = 0.f;
	
	float Dist = ToTarget.Size();
	
	if (Dist < MinAimDistance)
	{
		ToTarget = ToTarget.GetSafeNormal() * MinAimDistance;
	}
	
	FVector AdjustedAimTarget = PlayerLoc + ToTarget;
	
	FVector Start = PlayerSkeletalMeshComp->GetSocketLocation(SocketName);
	FVector ShootDir = (AdjustedAimTarget - Start).GetSafeNormal();
	FVector End   = Start + ShootDir * Range;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1, Params);
	
	FColor LineColor = bHit ? FColor::Green : FColor::Red;
	
	DrawDebugLine(GetWorld(), Start, bHit ? Hit.ImpactPoint: End, LineColor, false, 1.5f, 0, 1.5f);
	if (bHit)
	{
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 6.0f, 8, FColor::Red, false, 1.5f);
	}
}

void UCombatComponent::Initialize(UPlayerStatsComponent* PlayerStatComponent, USkeletalMeshComponent* SkeletalMeshComponent)
{
	_PlayerStatsComponent = PlayerStatComponent;
	PlayerSkeletalMeshComp = SkeletalMeshComponent;
}

void UCombatComponent::SetAimTargetWorld(const FVector& WorldTarget)
{
	AimTarget = WorldTarget;
}

bool UCombatComponent::Fire(const UFireModeData* FireMode)
{
	if (!FireMode || !_PlayerStatsComponent || !PlayerSkeletalMeshComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCombatComponent::Fire() is nullptr"));
		return false;
	}
	
	switch (FireMode->FireModeType)
	{
	case EFireModeType::Hitscan: return ExecuteHitscan(FireMode);
	case EFireModeType::Projectile: return ExecuteProjectile(FireMode);
	}
	
	return false;
	
}

bool UCombatComponent::ExecuteHitscan(const UFireModeData* FireMode)
{
	if (FirePoints.Num() == 0) return false;
	
	const FPlayerStats& BaseStats = _PlayerStatsComponent->GetPlayerStat();
	float Damage;
	float Range;
	
	if (FireMode->FireType == EFireType::Primary)
	{
		Damage = BaseStats.PrimaryAttackDamage;
		Range = BaseStats.PrimaryFireRange;
	}
	else
	{
		Damage = BaseStats.SecondaryAttackDamage;
		Range = BaseStats.SecondaryFireRange;
	}
	
	if (FireMode->bFireFromAllFirePoints)
	{
		for (const FFirePointData& FirePoint : FirePoints)
		{
			FireHitscan(FirePoint.MuzzleSocketName, Damage, Range);
		}
	}
	else
	{
		FireHitscan(FirePoints[0].MuzzleSocketName, Damage, Range);
	}
	
	return true;
}

bool UCombatComponent::ExecuteProjectile(const UFireModeData* FireMode)
{
	return false;
}



