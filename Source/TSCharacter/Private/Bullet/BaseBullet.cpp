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
	Movement->StopMovementImmediately();
}

void ABaseBullet::OnActivated()
{
	Super::OnActivated();
}

void ABaseBullet::OnDeactivated()
{
	Super::OnDeactivated();
}

void ABaseBullet::ActivateBullet(float Damage, float MaxRange, const FVector& Direction, const FVector& StartLocation)
{
	_Damage = Damage;
	_MaxRange = MaxRange;
	
	Movement->StopMovementImmediately();
	Movement->SetUpdatedComponent(nullptr);
	
	SetActorLocation(StartLocation);
	SetActorRotation(Direction.Rotation());
	
	Movement->SetUpdatedComponent(RootComponent);
	
	Movement->Velocity = Direction * Movement->InitialSpeed;
	Movement->Activate(true);
}

