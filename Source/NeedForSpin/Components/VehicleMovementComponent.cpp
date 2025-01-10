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

	// Update car rotation based on turn rate
    if (!FMath::IsNearlyZero(CurrentTurnRate))
    {
        FRotator NewRotation = GetOwner()->GetActorRotation();
		// TODO: check if actor is going forward or backward with vector math
		if(MovementVector.Y >= 0)
        	NewRotation.Yaw += CurrentTurnRate * DeltaTime;
		else
			NewRotation.Yaw -= CurrentTurnRate * DeltaTime; // basically inverting the turn direction when going backwards

        GetOwner()->SetActorRotation(NewRotation);
    }

	CurrentTurnRate = 0.f;
	MovementVector.Y = 0;
	MovementVector.X = 0;
  	GetOwner()->AddActorLocalOffset(CurrentVelocity, true);
}

void UVehicleMovementComponent::MoveForward(const FVector2D& Value) {
	UE_LOG(LogTemp, Warning, TEXT("We are in the vehicle movement component"));
	MovementVector = Value;
}

void UVehicleMovementComponent::Turn(const FVector2D& Value) {
	CurrentTurnRate = Value.X * TurnRate;
}