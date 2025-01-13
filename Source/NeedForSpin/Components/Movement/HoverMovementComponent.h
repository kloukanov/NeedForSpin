#pragma once

#include "CoreMinimal.h"
#include "BaseMovementComponent.h"
#include "HoverMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class NEEDFORSPIN_API UHoverMovementComponent : public UBaseMovementComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Variables", meta = (AllowPrivateAccess = "true"))
	float TurnOwnerActorRate;

protected:

	virtual void BeginPlay() override;

	void UpdateRotation();

public:	

	UHoverMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void MoveForward(const FVector2D& Value) override;

	virtual void Turn(const FVector2D& Value) override;
};
