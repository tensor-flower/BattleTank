// Guo Wanqi 2019

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UTankAimingComponent::SetBarrelRef(UStaticMeshComponent * barrelPtr)
{
	barrel = barrelPtr;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
													false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace, 
													FCollisionResponseParams::DefaultResponseParam,
													TArray<AActor*>(), true)) {
		auto aimDirection = tossVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s speed %s"), *GetOwner()->GetName(), *aimDirection.ToString())
	}
}

