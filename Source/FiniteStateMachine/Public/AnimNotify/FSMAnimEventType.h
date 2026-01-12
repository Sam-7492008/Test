#pragma once

#include "FSMAnimEventType.generated.h"

UENUM(BlueprintType)
enum class EFSMAnimEventType : uint8
{
	Trigger,
	Finished
};