#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

UCLASS()
class TSCHARACTER_API ABaseBullet : public AActor
{
	GENERATED_BODY()

public:
	ABaseBullet();
	
	void InitializeBullet(float Damage, float MaxRange, FVector Direction);

protected:
	virtual void BeginPlay() override;
	
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
