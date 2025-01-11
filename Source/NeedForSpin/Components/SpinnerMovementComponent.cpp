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

	UpdateRotation();

	MovementVector.Y = 0;
	MovementVector.X = 0;
  	GetOwner()->AddActorLocalOffset(CurrentVelocity, true);
}

void USpinnerMovementComponent::UpdateRotation() {
	FVector Location;
	FRotator Rotation;

	AController* OwnerController = Cast<APawn>(GetOwner())->GetController();
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector LookDirection = Rotation.Vector();

    FVector ActorLocation = GetOwner()->GetActorLocation();
    FVector TargetLocation = Location + (LookDirection * 10000.0f);
    FVector DirectionToTarget = (TargetLocation - ActorLocation).GetSafeNormal();
    FRotator TargetRotation = DirectionToTarget.Rotation();

    FRotator CurrentRotation =  GetOwner()->GetActorRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), TurnOwnerActorRate);
	NewRotation.Pitch = 0.0f;
    NewRotation.Roll = 0.0f;

    GetOwner()->SetActorRotation(NewRotation);
}

void USpinnerMovementComponent::MoveForward(const FVector2D& Value) {
	// UE_LOG(LogTemp, Warning, TEXT("We are in the Spinner movement component"));
	MovementVector = Value;
}

void USpinnerMovementComponent::Turn(const FVector2D& Value) {
	// only updating the right/left value
	MovementVector.X = Value.X;
}
