#include "TSPlayerPawn.h"

ATSPlayerPawn::ATSPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

