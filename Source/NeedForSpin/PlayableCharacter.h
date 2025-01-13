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

	// TODO: make this a skeletal mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	// TODO: make this a skeletal mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TorsoMesh;

	UPROPERTY(VisibleAnywhere, Category="Components") 
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Components") 
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBaseMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float TorsoTurnSpeed = 20.f;

	bool bIsFiring = false; 

public:

	APlayableCharacter();

protected:

	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);

	void Turn(const struct FInputActionValue& Value);

	void Look(const struct FInputActionValue& Value);

	void RotateTorso();

	void Shoot();

	void StopShoot();

	void Fire();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetUpPlayerMovementComponent(TSubclassOf<UBaseMovementComponent> _MovementComponent);

	UBaseMovementComponent* GetPlayerMovementComponent() const { return MovementComponent; }	

};
