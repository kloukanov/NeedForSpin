#include "BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	GunCurrentMagSize = GunMaxMagSize;
	GunCurrentBulletRounds = GunMaxBulletRounds;
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseWeapon::PullTrigger() {
	UE_LOG(LogTemp, Warning, TEXT("Pull trigger from BaseWeapon class"));

	FHitResult Hit;
	FVector ShotDirection; 

	GunTrace(Hit, ShotDirection);
	
	return false;
}

bool ABaseWeapon::GunTrace(FHitResult& OutHit, FVector& OutShotDirection) {
	UE_LOG(LogTemp, Warning, TEXT("GunTrace from BaseWeapon class"));
	return false;
}

