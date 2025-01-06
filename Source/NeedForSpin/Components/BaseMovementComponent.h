#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class NEEDFORSPIN_API UBaseMovementComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	float MovementSpeed = 50.f;

	virtual void BeginPlay() override;

public:	

	UBaseMovementComponent();

	float GetMovementSpeed() const { return MovementSpeed; }

	void SetMovementSpeed(float NewSpeed) { MovementSpeed = NewSpeed; }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Move() {};

};
