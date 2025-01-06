#include "VehicleMovementComponent.h"

UVehicleMovementComponent::UVehicleMovementComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UVehicleMovementComponent::BeginPlay() {
	Super::BeginPlay();
}

void UVehicleMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UVehicleMovementComponent::Move() {
	UE_LOG(LogTemp, Warning, TEXT("We are in the vehicle movement component"));
}