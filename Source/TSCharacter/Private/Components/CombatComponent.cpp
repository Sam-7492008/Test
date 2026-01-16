#include "Components/CombatComponent.h"

#include "PlayerStatData.h"
#include "Bullet/BaseBullet.h"
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
	
	PrimaryTimeSinceLastFire += DeltaTime;
	SecondaryTimeSinceLastFire += DeltaTime;
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
	
	CurrentFireMode = FireMode;
	const EFireType FireType = CurrentFireMode->FireType;
	
	const FWeaponStats WeaponStats = 
		(FireType == EFireType::Primary)
		? _PlayerStatsComponent->GetPrimaryWeaponStats()
		: _PlayerStatsComponent->GetSecondaryWeaponStats();
	
	const float FireRate = WeaponStats.BaseFireRate;
	if (FireRate <= 0.0f)
	{
		return false;
	}
	
	float& TimeSinceLastFire = GetTimeSinceLastFire(FireType);
	float& FireInterval = GetFireInterval(FireType);
	
	FireInterval = 1.0f / FireRate;
	if (TimeSinceLastFire < FireInterval)
	{
		return false;
	}
	
	if (ExecuteFire())
	{
		TimeSinceLastFire -= FireInterval;
		TimeSinceLastFire = FMath::Clamp(TimeSinceLastFire,0.0f,FireInterval);
		return true;
	}
	
	return false;
	
}

bool UCombatComponent::ExecuteFire()
{
	if (FirePoints.Num() == 0) return false;
	
	const FWeaponStats WeaponStats = 
	(CurrentFireMode->FireType == EFireType::Primary)
	? _PlayerStatsComponent->GetPrimaryWeaponStats()
	: _PlayerStatsComponent->GetSecondaryWeaponStats();
	float Damage;
	float Range;
	
	if (CurrentFireMode->FireType == EFireType::Primary)
	{
		Damage = WeaponStats.BaseDamage;
		Range = WeaponStats.BaseFireRange;
	}
	else
	{
		Damage = WeaponStats.BaseDamage;
		Range = WeaponStats.BaseFireRange;
	}
	
	if (CurrentFireMode->bFireFromAllFirePoints)
	{
		for (const FFirePointData& FirePoint : FirePoints)
		{
			(CurrentFireMode->FireModeType == EFireModeType::Hitscan)
			? FireHitscan(FirePoint.MuzzleSocketName, Damage, Range)
			: FireProjectile(FirePoint.MuzzleSocketName, Damage, Range);
		}
	}
	else
	{
		(CurrentFireMode->FireModeType == EFireModeType::Hitscan)
			? FireHitscan(FirePoints[0].MuzzleSocketName, Damage, Range)
			: FireProjectile(FirePoints[0].MuzzleSocketName, Damage, Range);
	}
	
	return true;
}

void UCombatComponent::FireProjectile(FName SocketName, float Damage, float Range)
{
	if (!PlayerSkeletalMeshComp || !PlayerSkeletalMeshComp->DoesSocketExist(SocketName) || !CurrentFireMode || !CurrentFireMode->ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("FireProjectile Error!"));
		return;
	}
	
	constexpr float MinAimDistance = 150.0f;
	
	UE_LOG(LogTemp, Warning, TEXT("FireProjectile called!"));
	
	FVector SpawnLocation = PlayerSkeletalMeshComp->GetSocketLocation(SocketName);
	FVector ShootDirection = ResolveFireDirection(SpawnLocation, MinAimDistance);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	
	ABaseBullet* Bullet = GetWorld()->SpawnActor<ABaseBullet>(
		CurrentFireMode->ProjectileClass,
		SpawnLocation,
		ShootDirection.Rotation(),
		SpawnParams);
	
	if (Bullet)
	{
		Bullet->InitializeBullet(Damage, Range, ShootDirection);
	}
	
}

void UCombatComponent::FireHitscan(FName SocketName, float Damage, float Range)
{
	if (!PlayerSkeletalMeshComp || !PlayerSkeletalMeshComp->DoesSocketExist(SocketName) || !CurrentFireMode)
		return;

	constexpr float MinAimDistance = 150.0f;
	
	FVector Start = PlayerSkeletalMeshComp->GetSocketLocation(SocketName);
	FVector ShootDir = ResolveFireDirection(Start, MinAimDistance);
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

FVector UCombatComponent::ResolveFireDirection(const FVector& FirePointWorldPosition, float MinAimDistance) const
{
	FVector ToTarget = AimTarget - FirePointWorldPosition;
	ToTarget.Z = 0.f;

	float Dist = ToTarget.Size();
	if (Dist < MinAimDistance)
	{
		ToTarget = ToTarget.GetSafeNormal() * MinAimDistance;
	}

	return ToTarget.GetSafeNormal();
}

float& UCombatComponent::GetFireInterval(EFireType FireType)
{
	return (FireType == EFireType::Primary) ? PrimaryFireInterval : SecondaryFireInterval;
}

float& UCombatComponent::GetTimeSinceLastFire(EFireType FireType)
{
	return (FireType == EFireType::Primary) ? PrimaryTimeSinceLastFire : SecondaryTimeSinceLastFire;
}


