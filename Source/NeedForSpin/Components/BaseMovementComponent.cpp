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

void UBaseMovementComponent::UpdateVelocity(double& MovementDirection, double& CurrentVelocityDirection, const float DeltaTime) {
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
