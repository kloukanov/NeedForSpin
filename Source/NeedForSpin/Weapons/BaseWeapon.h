#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class NEEDFORSPIN_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	float GunFireRange;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	float GunDamage;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	bool bIsAutomatic = false;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	bool bIsTwoHanded = false;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	float GunFireSpeed;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	int GunMaxMagSize;

	int GunCurrentMagSize;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	int GunMaxBulletRounds;

	int GunCurrentBulletRounds;

protected:

	virtual void BeginPlay() override;

	virtual bool GunTrace(FHitResult& OutHit, FVector& OutShotDirection);

public:	

	ABaseWeapon();

	virtual void Tick(float DeltaTime) override;

	virtual bool PullTrigger();

	bool GetIsAutomatic() const { return bIsAutomatic; }

	bool GetIsTwoHanded() const { return bIsTwoHanded; }

	float GetGunFireSpeed() const { return GunFireSpeed; }

	int GetGunCurrentMagSize() const { return GunCurrentMagSize; }

	int GetGunCurrentBulletRounds() const { return GunCurrentBulletRounds; }

	int GetGunMaxBulletRounds() const { return GunMaxBulletRounds; }

};
