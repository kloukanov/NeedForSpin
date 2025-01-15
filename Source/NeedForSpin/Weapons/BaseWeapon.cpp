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

	// TODO: muzzle flash particles
	// TODO: gun sound

	// check if we have enough bullets in the gun to shoot
	if(GunCurrentMagSize > 0) {
		GunCurrentMagSize--;

		FHitResult Hit;
		FVector ShotDirection; 

		bool bSuccess = GunTrace(Hit, ShotDirection);

		if(bSuccess){
			DrawDebugPoint(GetWorld(), Hit.Location, 5, FColor::Blue, true);
			AActor* HitActor = Hit.GetActor();
			
			if(HitActor){
				UE_LOG(LogTemp, Warning, TEXT("hit actor with name: %s"), *HitActor->GetActorNameOrLabel());
				// TODO: health component
			}
		}
	}else {
		//TODO: play empty shot sound
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("NUMBER OF BULLETS: %d / %d | %d / %d"), GunCurrentMagSize, GunMaxMagSize, GunCurrentBulletRounds, GunMaxBulletRounds);
	return true;
}

bool ABaseWeapon::GunTrace(FHitResult& OutHit, FVector& OutShotDirection) {
	UE_LOG(LogTemp, Warning, TEXT("GunTrace from BaseWeapon class"));
	
	FTransform MuzzleTransform = Mesh->GetSocketTransform(TEXT("MuzzleFlash"));
	FVector MuzzleLocation = MuzzleTransform.GetLocation();
	FVector EndShotLocation = MuzzleLocation + MuzzleTransform.GetRotation().Vector() * GunFireRange;
	OutShotDirection = MuzzleTransform.GetRotation().Vector();

	DrawDebugLine(GetWorld(), MuzzleLocation, EndShotLocation, FColor::Green, true, 5.f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OutHit, MuzzleLocation, EndShotLocation, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

