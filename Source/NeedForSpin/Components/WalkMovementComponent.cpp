#include "WalkMovementComponent.h"

UWalkMovementComponent::UWalkMovementComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UWalkMovementComponent::BeginPlay() {
	Super::BeginPlay();
}

void UWalkMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWalkMovementComponent::Move() {
	UE_LOG(LogTemp, Warning, TEXT("We are in the walk movement component"));
}
