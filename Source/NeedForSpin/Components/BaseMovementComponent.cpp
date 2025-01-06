#include "BaseMovementComponent.h"

UBaseMovementComponent::UBaseMovementComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseMovementComponent::BeginPlay() {
	Super::BeginPlay();
}

void UBaseMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

