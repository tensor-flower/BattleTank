// Guo Wanqi 2019

#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("aim component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector hitLocation)
{
	tankAimingComponent->Log(hitLocation, launchSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetName(), *hitLocation.operator/(100.f).ToString())
}

void ATank::SetBarrelRef(UStaticMeshComponent *barrelRef)
{
	tankAimingComponent->SetBarrelRef(barrelRef);
}

