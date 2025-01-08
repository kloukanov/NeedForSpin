#pragma once

#include "CoreMinimal.h"
#include "BaseMovementComponent.h"
#include "VehicleMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class NEEDFORSPIN_API UVehicleMovementComponent : public UBaseMovementComponent
{
	GENERATED_BODY()

private:

	void UpdateVelocity(double& MovementDirection, double& CurrentVelocityDirection, const float DeltaTime);

protected:

	virtual void BeginPlay() override;

public:	

	UVehicleMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Move(const FVector2D& Value) override;
	
};
