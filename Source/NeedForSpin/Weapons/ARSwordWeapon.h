#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "ARSwordWeapon.generated.h"

UCLASS()
class NEEDFORSPIN_API AARSwordWeapon : public ABaseWeapon
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual bool PullTrigger() override;
};
