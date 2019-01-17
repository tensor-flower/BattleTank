// Guo Wanqi 2019

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UTankAimingComponent::SetBarrelRef(UTankBarrel * barrelPtr)
{
	barrel = barrelPtr;
}

void UTankAimingComponent::SetTurretRef(UTankTurret *turretPtr)
{
	turret = turretPtr;
}

void UTankAimingComponent::AimComponentAim(FVector outHitLocation, float speed)
{
	//auto barrelPosition = barrel->GetComponentLocation();
	if (!barrel || !turret) return;
	
	FVector tossVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	FCollisionResponseParams responseParams;
	TArray<AActor*> actorsToIgnore;
	/*UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(),
		*outHitLocation.operator/(100.f).ToString(),
		*barrelPosition.operator/(100.f).ToString())*/
	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, tossVelocity, startLocation, outHitLocation, speed,
													false, 0, 0,
													ESuggestProjVelocityTraceOption::DoNotTrace,
													responseParams,
													actorsToIgnore,
													true);
	//AI always has aimSolution when not trace
	if(haveAimSolution){
		FVector aimDirection = tossVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s speed %s"), *GetOwner()->GetName(), *aimDirection.ToString())
		//UE_LOG(LogTemp, Warning, TEXT("%s has aim solution"), *GetOwner()->GetFName().ToString())	
		FRotator aimRotator = aimDirection.Rotation();
		MoveBarrel(aimRotator);
		//MoveTurret(aimRotator);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("%s no aim solution"), *GetOwner()->GetFName().ToString())
	}
}

void UTankAimingComponent::MoveBarrel(FRotator aimDirection)
{
	FRotator barrelRotator = barrel->GetComponentRotation();
	FRotator aimRotator = aimDirection;
	FRotator diff = aimRotator - barrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("%s aim rotator %s"), *GetOwner()->GetName(), *aimRotator.ToString())
	//get barrel rotation, set barrel rotation using desired direction and speed
	//clamp it
	barrel->Elevate(diff.Pitch);
	if(FMath::Abs(diff.Yaw)<180)
		turret->TurretYaw(diff.Yaw);
	else
		turret->TurretYaw(-diff.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("%f yaw"), diff.Yaw)
	//make use of the fact that barrel has no yaw
}

void UTankAimingComponent::MoveTurret(FRotator aimDirection)
{
	FRotator turretRotator = turret->GetComponentRotation();
	FRotator aimRotator = aimDirection;
	FRotator diff = aimRotator - turretRotator;
	turret->TurretYaw(diff.Yaw);
}

