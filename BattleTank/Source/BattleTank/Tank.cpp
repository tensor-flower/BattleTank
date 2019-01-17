// Guo Wanqi 2019

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("aim component"));
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
	tankAimingComponent->AimComponentAim(hitLocation, launchSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetName(), *hitLocation.operator/(100.f).ToString())
}

void ATank::SetBarrelRef(UTankBarrel *barrelRef)
{
	tankAimingComponent->SetBarrelRef(barrelRef);
	barrel = barrelRef;
}

void ATank::SetTurretRef(UTankTurret *turretRef)
{
	tankAimingComponent->SetTurretRef(turretRef);
}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("fire method called by BP"))
	if (!barrel) return;
	//UClass* AProjectile;
	FVector spawnLocation = barrel->GetSocketLocation(FName("Projectile"));
	FRotator spawnRotator = spawnLocation.Rotation();
	GetWorld()->SpawnActor<AProjectile>(projectileBP, spawnLocation, spawnRotator);
}
