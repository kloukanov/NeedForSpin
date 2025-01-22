#include "PlayableCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Movement/BaseMovementComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Components/Torso/BaseTorsoComponent.h"

APlayableCharacter::APlayableCharacter() {
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	PlayerBaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	PlayerBaseMesh->SetupAttachment(CapsuleComp);

	PlayerTorsoMeshComponent = CreateDefaultSubobject<UBaseTorsoComponent>(TEXT("Torso Mesh Component"));
	PlayerTorsoMeshComponent->SetupAttachment(PlayerBaseMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

}

void APlayableCharacter::BeginPlay() {
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(PlayerTorsoMeshComponent, AttachmentRules, FName("GripPoint"));
	Weapon->SetOwner(this);
}

void APlayableCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APlayableCharacter::RotateTorso() {

	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint(Location, Rotation);

	FVector LookDirection = Rotation.Vector();

    FVector TorsoLocation = PlayerTorsoMeshComponent->GetComponentLocation();
    FVector TargetLocation = Location + (LookDirection * 10000.0f);
    FVector DirectionToTarget = (TargetLocation - TorsoLocation).GetSafeNormal();

    FRotator TargetRotation = DirectionToTarget.Rotation();

    FRotator CurrentRotation = PlayerTorsoMeshComponent->GetComponentRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), TorsoTurnSpeed);

    PlayerTorsoMeshComponent->SetWorldRotation(NewRotation);
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// locomotion
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Turn);
		// look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Look);
		// shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APlayableCharacter::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &APlayableCharacter::StopShoot);
	}
}

void APlayableCharacter::Shoot() {
	UE_LOG(LogTemp, Warning, TEXT("We are shooting"));
	if(Weapon && !bIsFiring) {
		bIsFiring = true;
		Fire();
	}
}

void APlayableCharacter::StopShoot() {
	UE_LOG(LogTemp, Warning, TEXT("We stopped firing"));
	if(bIsFiring) {
		bIsFiring = false;
	}
}

void APlayableCharacter::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("we are firing"));
	if(Weapon) {
		Weapon->PullTrigger();
	}
}

void APlayableCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		RotateTorso();
	}
}

void APlayableCharacter::Turn(const struct FInputActionValue& Value) {
	if(MovementComponent) {
		MovementComponent->Turn(Value.Get<FVector2D>());
	}else {
		UE_LOG(LogTemp, Warning, TEXT("No Movement Component found"));
	}
}

void APlayableCharacter::Move(const struct FInputActionValue& Value) {
	if(MovementComponent) {
		MovementComponent->MoveForward(Value.Get<FVector2D>());
	}else {
		UE_LOG(LogTemp, Warning, TEXT("No Movement Component found"));
	}
}

void APlayableCharacter::SetUpPlayerMovementComponent(TSubclassOf<UBaseMovementComponent> MovementComponentClass) {
	if(MovementComponent) {
		MovementComponent->DestroyComponent();
		MovementComponent = nullptr;
	}

	if(MovementComponent == nullptr) {
		MovementComponent = NewObject<UBaseMovementComponent>(this, MovementComponentClass);
		MovementComponent->RegisterComponent();
		UE_LOG(LogTemp, Warning, TEXT("added new movement component of type: %s"), *MovementComponentClass->GetFName().ToString());
	}
}