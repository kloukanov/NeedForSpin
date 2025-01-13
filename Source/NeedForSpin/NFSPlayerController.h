#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NFSPlayerController.generated.h"

UCLASS()
class NEEDFORSPIN_API ANFSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Input")
    class UInputMappingContext* InputMappingContext;

	virtual void BeginPlay() override;

};
