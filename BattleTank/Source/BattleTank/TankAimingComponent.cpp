// Guo Wanqi 2019

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

//assign firing status Enum
//TODO add state where line trace fail
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (GetWorld()->GetTimeSeconds() - lastFireTime < cooldownTimeInSeconds) {
		firingStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		firingStatus = EFiringStatus::Aiming;
	}
	else
	{
		firingStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	lastFireTime = GetWorld()->GetTimeSeconds();
}

//set up barrel and turret pointers
void UTankAimingComponent::Initialise(UTankBarrel * barrelToSet, UTankTurret * turretToSet)
{
	barrel = barrelToSet;
	turret = turretToSet;
}

void UTankAimingComponent::AimComponentAim(FVector outHitLocation)
{
	if (!ensure(barrel) || !ensure(turret)) return;
	
	FVector tossVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	FCollisionResponseParams responseParams;
	TArray<AActor*> actorsToIgnore;
	/*UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(),
		*outHitLocation.operator/(100.f).ToString(),
		*barrelPosition.operator/(100.f).ToString())*/
	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, tossVelocity, 
													startLocation, outHitLocation, speed,
													false, 0, 0,
													ESuggestProjVelocityTraceOption::DoNotTrace,
													responseParams,
													actorsToIgnore,
													false);

	if(haveAimSolution){
		aimDirection = tossVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s aim direction %s"), *GetOwner()->GetName(), *aimDirection.ToString())
		FRotator aimRotator = aimDirection.Rotation();
		MoveBarrel(aimRotator);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("%s no aim solution"), *GetOwner()->GetFName().ToString())
	}
}

void UTankAimingComponent::MoveBarrel(FRotator aimRotator)
{
	if (!ensure(barrel))	return;
	FRotator barrelRotator = barrel->GetComponentRotation();
	FRotator diff = aimRotator - barrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("%s aim rotator %s"), *GetOwner()->GetName(), *aimRotator.ToString())
	//get barrel rotation, set barrel rotation using desired direction and speed
	//clamp it
	barrel->Elevate(diff.Pitch);
	if (!ensure(turret))	return;
	if(FMath::Abs(diff.Yaw)<180)
		turret->TurretYaw(diff.Yaw);
	else
		turret->TurretYaw(-diff.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("%f yaw"), diff.Yaw)
	//make use of the fact that barrel has no yaw
}

//useless function
void UTankAimingComponent::MoveTurret(FRotator aimRotator)
{
	FRotator turretRotator = turret->GetComponentRotation();
	FRotator diff = aimRotator - turretRotator;
	turret->TurretYaw(diff.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(barrel && projectileBP))	return;
	bool isReloaded = (GetWorld()->GetTimeSeconds() - lastFireTime) > cooldownTimeInSeconds;
	if (isReloaded) {
		FVector spawnLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator spawnRotator = barrel->GetSocketRotation(FName("Projectile"));
		//instantiate projectile
		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP, spawnLocation, spawnRotator);
		projectile->LaunchProjectile(speed);

		lastFireTime = GetWorld()->GetTimeSeconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(barrel))	return false;
	//UE_LOG(LogTemp, Warning, TEXT("%s aim direction %s"), *GetOwner()->GetName(), *aimDirection.ToString())
	float tolerance = 0.1f;
	return !aimDirection.Equals(barrel->GetForwardVector(), tolerance);
}