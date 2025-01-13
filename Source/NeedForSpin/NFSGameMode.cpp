#include "NFSGameMode.h"
#include "PlayableCharacter.h"
#include "Components/Movement/BaseMovementComponent.h"

void ANFSGameMode::BeginPlay() {
	Super::BeginPlay();

	// TODO: remove this is TEMP ---------
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
        EnableInput(PlayerController);

        if (InputComponent) {
            InputComponent->BindAction("ChangeMovementComponent", IE_Pressed, this, &ANFSGameMode::BuildPlayerCharacter);
        }
    }
	// --------------------------------
	
}

void ANFSGameMode::BuildPlayerCharacter() {
    if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
        if(APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(PlayerController->GetPawn())) {
            // TODO: remove this is TEMP ---------
            if(PlayableCharacter->GetPlayerMovementComponent() == nullptr) {
                PlayableCharacter->SetUpPlayerMovementComponent(HoverMovementComponentClass);
            }else if(PlayableCharacter->GetPlayerMovementComponent()->IsA(HoverMovementComponentClass)){
                PlayableCharacter->SetUpPlayerMovementComponent(VehicleMovementComponentClass);
            } else {
                PlayableCharacter->SetUpPlayerMovementComponent(HoverMovementComponentClass);
            }
            // --------------------------------
        }
    }
}