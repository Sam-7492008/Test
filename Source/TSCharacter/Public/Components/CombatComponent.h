#pragma once

#include "CoreMinimal.h"
#include "Data/FirePointData.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UFireModeData;
class UPlayerStatsComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSCHARACTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatComponent();
	
	void Initialize(UPlayerStatsComponent* PlayerStatComponent, USkeletalMeshComponent* SkeletalMeshComponent);
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

	FVector AimTarget = FVector::ForwardVector;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FFirePointData> FirePoints;
	
	FVector PrimaryAimDirection = FVector::ForwardVector;
	FVector SecondaryAimDirection = FVector::ForwardVector;
	FVector PrimaryFirePoint = FVector::ZeroVector;
	FVector SecondaryFirePoint = FVector::ZeroVector;	
	
private:
	bool ExecuteHitscan(const UFireModeData* FireMode);
	bool ExecuteProjectile(const UFireModeData* FireMode);
	
	void FireHitscan(FName SocketName, float Damage, float Range);
	
};
