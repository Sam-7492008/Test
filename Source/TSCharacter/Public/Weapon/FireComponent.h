// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireType.h"
#include "Components/ActorComponent.h"
#include "FireComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSCHARACTER_API UFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFireComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	EFireType FireType = EFireType::Hitscan;
	
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float FireRate = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float Damage = 25.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	float Range = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
	FName MuzzleSocketName = "Muzzle";
	
	// Runtime
	UPROPERTY()
	AActor* OwnerActor = nullptr;
	
	bool bWantsToShoot = false;
	
	// Functions
	void FireHitscan();
};
