#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class NEEDFORSPIN_API APlayableCharacter : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category="Components") 
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Components") 
	class UCameraComponent* Camera;

public:

	APlayableCharacter();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
