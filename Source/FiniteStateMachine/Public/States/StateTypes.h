#pragma once
#include "StateTypes.generated.h"

UENUM(BlueprintType)
enum class EFSMStateTypes : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Locomotion UMETA(DisplayName = "Locomotion"),
	Sprint UMETA(DisplayName = "Sprint"),
	InAir UMETA(DisplayName = "In Air"),
	Jump UMETA(DisplayName = "Jump"),
	Land UMETA(DisplayName = "Land"),
	Dash UMETA(DisplayName = "Dash")
};