#pragma once

#include "CoreMinimal.h"
#include "PlayerAnimState.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimState : uint8
{
	Locomotion UMETA(DisplayName = "Locomotion"),
	Jump UMETA(DisplayName = "Jump"),
	InAir UMETA(DisplayName = "In Air"),
	Land UMETA(DisplayName = "Land"),
};