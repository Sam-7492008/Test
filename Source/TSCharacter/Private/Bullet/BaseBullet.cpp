#include "Bullet/BaseBullet.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABaseBullet::ABaseBullet()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMeshComp;
	
	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->SetupAttachment(RootComponent);
	
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->InitialSpeed = 2000.0f;
	Movement->MaxSpeed = 2000.0f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 0.0f;
}

void ABaseBullet::InitializeBullet(float Damage, float MaxRange, FVector Direction)
{
	_Damage = Damage;
	_MaxRange = MaxRange;
	
	Movement->Velocity = Direction * Movement->InitialSpeed;
}

void ABaseBullet::BeginPlay()
{
	Super::BeginPlay();
}

