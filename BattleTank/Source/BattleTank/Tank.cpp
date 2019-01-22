// Guo Wanqi 2019

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > cooldownTimeInSeconds;
	if (barrel && isReloaded) {
		FVector spawnLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator spawnRotator = barrel->GetSocketRotation(FName("Projectile"));
		//instantiate projectile
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, spawnLocation, spawnRotator);
		projectile->LaunchProjectile(launchSpeed);

		lastFireTime = FPlatformTime::Seconds();
	}
}
