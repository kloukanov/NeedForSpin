#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NFSGameMode.generated.h"

UCLASS()
class NEEDFORSPIN_API ANFSGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Components", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UBaseMovementComponent> VehicleMovementComponentClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Components", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UBaseMovementComponent> WalkMovementComponentClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Components", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class UBaseMovementComponent> SpinnerMovementComponentClass;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void BuildPlayerCharacter();
	
};
