#pragma once

#include "CoreMinimal.h"
#include "PlayerAnimState.h"
#include "StateContext.generated.h"

enum class EPlayerAnimState : uint8;
class IStateMachineOwner;
class UStateData;

USTRUCT()
struct FStateContext
{
	GENERATED_BODY()
	
	TScriptInterface<IStateMachineOwner> Owner = nullptr;
	
	UPROPERTY()
	UStateData* StateData = nullptr;
	
	EPlayerAnimState AnimState = EPlayerAnimState::Locomotion;
	
	float DeltaTime = 0.0f;
	float TimeInSeconds = 0.0f;
	
};
