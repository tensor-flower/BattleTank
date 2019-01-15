// Guo Wanqi 2019

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

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

void UTankAimingComponent::Log(FVector outHitLocation, float speed)
{
	auto barrelPosition = barrel->GetComponentLocation();
	FVector tossVelocity;
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));

	/*UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *GetOwner()->GetName(),
		*outHitLocation.operator/(100.f).ToString(),
		*barrelPosition.ToString())*/
	if (UGameplayStatics::SuggestProjectileVelocity(this, tossVelocity, startLocation, outHitLocation, speed, 
													false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto aimDirection = tossVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s speed %s"), *GetOwner()->GetName(), *aimDirection.ToString())
		MoveBarrel(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	FRotator barrelRotator = barrel->GetComponentRotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator diff = aimRotator - barrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("%s aim rotator %s"), *GetOwner()->GetName(), *aimRotator.ToString())
		//get barrel rotation, set barrel rotation using desired direction and speed
		//clamp it
	barrel->Elevate(5.f);
}

