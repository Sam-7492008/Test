// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PooledObject.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


UCLASS(ClassGroup=(ObjectPool), meta=(BlueprintSpawnableComponent))
class OBJECTPOOL_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UObjectPoolComponent();
	
	APooledObject* SpawnPooledObject();
	
	UPROPERTY(EditAnywhere, Category="Object Pool")
	TSubclassOf<APooledObject> PooledObjectClass;
	
	UPROPERTY(EditAnywhere, Category="Object Pool")
	int PoolSize = 20;
	
	UPROPERTY(EditAnywhere, Category="Object Pool")
	float PooledObjectLifeSpan = 0.0f;
	
	UFUNCTION()
	void OnPooledObjectDespawn(APooledObject* PoolActor);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Object Pool")
	TArray<APooledObject*> ObjectPool;
	
	TArray<int> SpawnedPoolIndexes;
	
};
