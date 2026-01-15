#pragma once

#include "StatsModifier.h"
#include "Engine/DataAsset.h"
#include "UpgradeStatsData.generated.h"

UCLASS()
class UUpgradeStatsData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FStatsModifier Modifier;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxStackSize = 5;
	
};
