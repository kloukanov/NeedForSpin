#pragma once

#include "CoreMinimal.h"
#include "BaseMovementComponent.h"
#include "WalkMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class NEEDFORSPIN_API UWalkMovementComponent : public UBaseMovementComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:	

	UWalkMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Move(const FVector2D& Value) override;

};
