// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"


APooledObject::APooledObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APooledObject::SetActive(bool _bIsActve)
{
	bIsActive = _bIsActve;
	SetActorHiddenInGame(!bIsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APooledObject::Deactivate, LifeSpan, false);
	
	if (bIsActive)
	{
		OnActivated();
	}
}

void APooledObject::Deactivate()
{
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
	OnDeactivated();
}

void APooledObject::SetObjectLifeSpan(float _LifeSpan)
{
	LifeSpan = _LifeSpan;
}

void APooledObject::SetPoolIndex(int _PoolIndex)
{
	PoolIndex = _PoolIndex;
}

bool APooledObject::IsActive() const
{
	return bIsActive;
}

int APooledObject::GetPoolIndex() const
{
	return PoolIndex;
}

void APooledObject::OnActivated()
{
}

void APooledObject::OnDeactivated()
{
}

