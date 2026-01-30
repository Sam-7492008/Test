#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StateData.generated.h"

UCLASS()
class FINITESTATEMACHINE_API UStateData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	float MoveSpeed = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	float SprintSpeed = 750.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	float InAirSpeed = 200.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dash")
	float DashDistance = 12000.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dash")
	float DashStrengthInAir = 2000.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dash")
	float DashDuration = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dash")
	float DashCooldown = 0.8f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dash")
	UCurveFloat* DashCurve;
	
	UPROPERTY(EditAnywhere, Category="Dash")
	UParticleSystem* ArmDashEmitter;
	
	UPROPERTY(EditAnywhere, Category="Dash")
	UParticleSystem* LegDashEmitter;
};
