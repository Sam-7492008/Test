#pragma once

#include "FirePointData.generated.h"

USTRUCT(BlueprintType)
struct FFirePointData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MuzzleSocketName;	
};
