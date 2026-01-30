// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, PoolActor);

UCLASS()
class OBJECTPOOL_API APooledObject : public AActor
{
	GENERATED_BODY()

public:
	APooledObject();
	
	FOnPooledObjectDespawn OnPooledObjectDespawn;
	
	UFUNCTION(BlueprintCallable, Category="Pooled Object")
	void Deactivate();
	
	void SetActive(bool _bIsActve);
	void SetObjectLifeSpan(float _LifeSpan);
	void SetPoolIndex(int _PoolIndex);
	
	bool IsActive() const;
	int GetPoolIndex() const;
	
protected:
	
	virtual void OnActivated();
	virtual void OnDeactivated();
	
	bool bIsActive;
	float LifeSpan = 0.0f;
	int PoolIndex;
	
	FTimerHandle LifeSpanTimer;
};
