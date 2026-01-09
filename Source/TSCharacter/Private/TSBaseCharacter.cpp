// Fill out your copyright notice in the Description page of Project Settings.


#include "TSBaseCharacter.h"


// Sets default values
ATSBaseCharacter::ATSBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
