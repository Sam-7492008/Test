#include "StateMachineComponent.h"
#include "StateBase.h"
#include "States/StateTypes.h"

UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!_CurrentState) return;
	
	Context.DeltaTime = DeltaTime;
	_CurrentState->Update(Context);
	
}

void UStateMachineComponent::Initialize(UStateBase* InitialState)
{
	_CurrentState = InitialState;
	_CurrentState->Enter(Context);
}

void UStateMachineComponent::InitializeOwner(TScriptInterface<IStateMachineOwner> Owner)
{
	Context.Owner = Owner;
}

void UStateMachineComponent::RegisterState(UStateBase* State)
{
	if (!State) return;
	States.Add(State->GetStateType(), State);
}

void UStateMachineComponent::ChangeState(EFSMStateTypes NewState)
{
	if (!States.Contains(NewState)) return;
	
	if (!_CurrentState || States[NewState] == _CurrentState) return;
	
	_CurrentState->Exit();
	_CurrentState = States[NewState];
	_CurrentState->Enter(Context);
}

