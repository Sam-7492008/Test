#pragma once
#include "StateTypes.generated.h"

UENUM(BlueprintType)
enum class EFSMStateTypes : uint8
{
	Idle,
	Locomotion,
	Sprint,
	InAir
};