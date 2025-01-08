#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class NEEDFORSPIN_API UBaseMovementComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	FVector CurrentVelocity;

	FVector2D MovementVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
    float Acceleration;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
	float Deceleration;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed;

	virtual void BeginPlay() override;

public:	

	UBaseMovementComponent();

	FVector GetCurrentVelocity() const { return CurrentVelocity; }

	float GetAcceleration() const { return Acceleration; }

	float GetDeceleration() const { return Deceleration; }

	float GetMaxSpeed() const { return MaxSpeed; }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Move(const FVector2D& Value) {};

};
