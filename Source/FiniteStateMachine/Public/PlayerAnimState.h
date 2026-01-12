#pragma once

#include "CoreMinimal.h"
#include "PlayerAnimState.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimState : uint8
{
	Locomotion UMETA(DisplayName = "Locomotion"),
	InAir UMETA(DisplayName = "In Air"),
	Land UMETA(DisplayName = "Land"),
	Dash UMETA(DisplayName = "Dash")
};