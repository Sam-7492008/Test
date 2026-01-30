#include "ObjectPoolComponent.h"


UObjectPoolComponent::UObjectPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (PooledObjectClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (int i = 0; i < PoolSize; i++)
			{
				APooledObject* PooledObject = World->SpawnActor<APooledObject>(PooledObjectClass, FVector::ZeroVector, FRotator::ZeroRotator);
				
				if (PooledObject != nullptr)
				{
					PooledObject->SetActive(false);
					PooledObject->SetPoolIndex(i);
					PooledObject->OnPooledObjectDespawn.AddDynamic(this, &UObjectPoolComponent::OnPooledObjectDespawn);
					ObjectPool.Add(PooledObject);
				}
			}
		}
	}
	
}

APooledObject* UObjectPoolComponent::SpawnPooledObject()
{
	for (APooledObject* PooledObject : ObjectPool)
	{
		if (PooledObject != nullptr && !PooledObject->IsActive())
		{
			PooledObject->SetObjectLifeSpan(PooledObjectLifeSpan);
			PooledObject->SetActive(true);
			SpawnedPoolIndexes.Add(PooledObject->GetPoolIndex());
			
			return PooledObject;
		}
	}
	
	if (SpawnedPoolIndexes.Num() > 0)
	{
		int PooledObjectIndex = SpawnedPoolIndexes[0];
		SpawnedPoolIndexes.RemoveAt(PooledObjectIndex);
		APooledObject* PooledObject = ObjectPool[PooledObjectIndex];
		
		if (PooledObject != nullptr)
		{
			PooledObject->SetActive(false);
			PooledObject->TeleportTo(FVector::ZeroVector, FRotator::ZeroRotator);
			PooledObject->SetObjectLifeSpan(PooledObjectLifeSpan);
			PooledObject->SetActive(true);
			SpawnedPoolIndexes.Add(PooledObject->GetPoolIndex());
			
			return PooledObject;
		}
		
	}
	
	return nullptr;
}

void UObjectPoolComponent::OnPooledObjectDespawn(APooledObject* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}

