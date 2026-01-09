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
	
};
