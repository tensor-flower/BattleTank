// Guo Wanqi 2019

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
//#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//this is moved to BP spawnable
	//tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("aim component"));
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

void ATank::AimAt(FVector hitLocation)
{
	if (!tankAimingComponent) { 
		UE_LOG(LogTemp, Warning, TEXT("no aim component"))
		return; 
	}
	tankAimingComponent->AimComponentAim(hitLocation, launchSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetName(), *hitLocation.operator/(100.f).ToString())
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
