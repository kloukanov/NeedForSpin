#include "SpinnerMovementComponent.h"

USpinnerMovementComponent::USpinnerMovementComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void USpinnerMovementComponent::BeginPlay() {
	Super::BeginPlay();
}

void USpinnerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update forward/backward velocity
	UpdateVelocity(MovementVector.Y, CurrentVelocity.X, DeltaTime);
	// Update right/left velocity
	UpdateVelocity(MovementVector.X, CurrentVelocity.Y, DeltaTime);

	MovementVector.Y = 0;
	MovementVector.X = 0;
  	GetOwner()->AddActorLocalOffset(CurrentVelocity, true);
}

void USpinnerMovementComponent::MoveForward(const FVector2D& Value) {
	UE_LOG(LogTemp, Warning, TEXT("We are in the Spinner movement component"));
	MovementVector = Value;
}

void USpinnerMovementComponent::Turn(const FVector2D& Value) {
	// only updating the right/left value
	MovementVector.X = Value.X;
}
