#pragma once

#include "CoreMinimal.h"
#include "StateContext.generated.h"

class IStateMachineOwner;
class UStateData;

USTRUCT()
struct FStateContext
{
	GENERATED_BODY()
	
	TScriptInterface<IStateMachineOwner> Owner = nullptr;
	
	UPROPERTY()
	UStateData* StateData = nullptr;
	
	float DeltaTime = 0.0f;
	
};
