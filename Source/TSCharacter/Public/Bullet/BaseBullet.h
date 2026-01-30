#pragma once

#include "CoreMinimal.h"
#include "PooledObject.h"
#include "BaseBullet.generated.h"

UCLASS()
class TSCHARACTER_API ABaseBullet : public APooledObject
{
	GENERATED_BODY()

public:
	ABaseBullet();
	
	void ActivateBullet(float Damage, float MaxRange, const FVector& Direction, const FVector& StartLocation);

protected:

	virtual void OnActivated() override;
	virtual void OnDeactivated() override;
	
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* Movement;
	
private:
	float _Damage = 0.0f;
	float _MaxRange = 0.0f;
	FVector _StartLocation = FVector::ZeroVector;
};
