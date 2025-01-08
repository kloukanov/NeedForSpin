#include "VehicleMovementComponent.h"

UVehicleMovementComponent::UVehicleMovementComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UVehicleMovementComponent::BeginPlay() {
	Super::BeginPlay();
}

void UVehicleMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update forward/backward velocity
	UpdateVelocity(MovementVector.Y, CurrentVelocity.X, DeltaTime);
	// Update right/left velocity
	UpdateVelocity(MovementVector.X, CurrentVelocity.Y, DeltaTime);

	MovementVector.Y = 0;
	MovementVector.X = 0;
  	GetOwner()->AddActorLocalOffset(CurrentVelocity, true);
}

void UVehicleMovementComponent::UpdateVelocity(double& MovementDirection, double& CurrentVelocityDirection, const float DeltaTime) {
	if(MovementDirection == 0.0f && GetOwner()->GetVelocity() == FVector::ZeroVector) {
		CurrentVelocityDirection = 0;
		return;
	}

	// Update forward/backward/right/left velocity
	if (FMath::Abs(MovementDirection) > KINDA_SMALL_NUMBER) {
		CurrentVelocityDirection += MovementDirection * Acceleration * DeltaTime;
		CurrentVelocityDirection = FMath::Clamp(CurrentVelocityDirection, -MaxSpeed, MaxSpeed);
	}
	else {
		// Apply deceleration when moving forward/right
		if (CurrentVelocityDirection > 0) {
			CurrentVelocityDirection -= Deceleration * DeltaTime;
			if (CurrentVelocityDirection < 0)
				CurrentVelocityDirection = 0;
		}
		// Apply deceleration when moving backward/left
		else if (CurrentVelocityDirection < 0) {
			CurrentVelocityDirection += Deceleration * DeltaTime;
			if (CurrentVelocityDirection > 0)
				CurrentVelocityDirection = 0;
		}
	}
}

void UVehicleMovementComponent::Move(const FVector2D& Value) {
	UE_LOG(LogTemp, Warning, TEXT("We are in the vehicle movement component"));
	MovementVector = Value;
}