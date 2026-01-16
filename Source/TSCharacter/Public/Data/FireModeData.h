#pragma once
#include "Engine/DataAsset.h"
#include "FireModeData.generated.h"

class ABaseBullet;

UENUM(BlueprintType)
enum class EFireModeType : uint8
{
	Hitscan,
	Projectile
};

UENUM(BlueprintType)
enum class EFireType : uint8
{
	Primary,
	Secondary
};

UCLASS(BlueprintType)
class UFireModeData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFireModeType FireModeType = EFireModeType::Hitscan;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFireType FireType = EFireType::Primary;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bFireFromAllFirePoints = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseBullet> ProjectileClass;
	
};
