#pragma once

#include "CoreMinimal.h"
#include "Data/FirePointData.h"
#include "Components/ActorComponent.h"
#include "Data/FireModeData.h"
#include "CombatComponent.generated.h"

class UObjectPoolComponent;
class UFireModeData;
class UPlayerStatsComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSCHARACTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();
	
	void Initialize(UPlayerStatsComponent* PlayerStatComponent, USkeletalMeshComponent* SkeletalMeshComponent, UObjectPoolComponent* ObjectPoolComponent);
	void SetAimTargetWorld(const FVector& WorldTarget);
	
	bool Fire(const UFireModeData* FireMode);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPROPERTY()
	USkeletalMeshComponent* PlayerSkeletalMeshComp;
	
	UPROPERTY()
	UPlayerStatsComponent* _PlayerStatsComponent = nullptr;
	
	UPROPERTY()
	UObjectPoolComponent* _ObjectPoolComponent = nullptr;

	FVector AimTarget = FVector::ForwardVector;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FFirePointData> FirePoints;
	
	FVector PrimaryAimDirection = FVector::ForwardVector;
	FVector SecondaryAimDirection = FVector::ForwardVector;
	FVector PrimaryFirePoint = FVector::ZeroVector;
	FVector SecondaryFirePoint = FVector::ZeroVector;	
	
	float NextPrimaryFireTime = 0.0f;
	float NextSecondaryFireTime = 0.0f;
	
	UPROPERTY(VisibleAnywhere)
	const UFireModeData* CurrentFireMode = nullptr;
	
private:
	bool ExecuteFire();
	
	void FireProjectile(FName SocketName, float Damage, float Range);
	void FireHitscan(FName SocketName, float Damage, float Range);
	
	FVector ResolveFireDirection(const FVector& FirePointWorldPosition, float MinAimDistance) const;
	
	float& GetNextFireTime(EFireType FireType);
	
};
