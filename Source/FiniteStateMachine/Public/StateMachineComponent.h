#pragma once

#include "CoreMinimal.h"
#include "StateContext.h"
#include "Components/ActorComponent.h"
#include "States/StateTypes.h"
#include "StateMachineComponent.generated.h"

class IStateMachineOwner;
class UStateData;
class UStateBase;

UCLASS(ClassGroup=(FiniteStateMachine), meta=(BlueprintSpawnableComponent))
class FINITESTATEMACHINE_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TMap<EFSMStateTypes, UStateBase*> States;
	
	UPROPERTY(VisibleAnywhere, Category="State")
	UStateBase* _CurrentState;
	
	UPROPERTY()
	FStateContext Context;
	
protected:
	virtual void BeginPlay() override;
	
public:
	UStateMachineComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="State Data")
	const UStateData* StateData;
	
	void Initialize(UStateBase* InitialState);
	void InitializeOwner(TScriptInterface<IStateMachineOwner> Owner);
	void RegisterState(UStateBase* State);
	void ChangeState(EFSMStateTypes NewState);
	
};
