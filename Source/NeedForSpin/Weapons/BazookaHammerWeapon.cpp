#include "BazookaHammerWeapon.h"

void ABazookaHammerWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABazookaHammerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// TODO: spawn rocket projectile
bool ABazookaHammerWeapon::PullTrigger() {
    UE_LOG(LogTemp, Warning, TEXT("pull trigger from BazookaHammerWeapon class"));
    return false;
}


