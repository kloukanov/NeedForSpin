#include "PlayableCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BaseMovementComponent.h"

APlayableCharacter::APlayableCharacter() {
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

}

void APlayableCharacter::BeginPlay() {
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void APlayableCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// locomotion
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Turn);
		// look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayableCharacter::Look);
	}
}

void APlayableCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
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