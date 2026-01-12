// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FireComponent.h"

UFireComponent::UFireComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFireComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UFireComponent::FireHitscan()
{
	
}

void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

