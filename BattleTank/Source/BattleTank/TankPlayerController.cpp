// Guo Wanqi 2019

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

ATank* ATankPlayerController::GetControlledTank() const {
	APawn* tank = GetPawn();
	return Cast<ATank>(tank);
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }
	FVector outHitLocation;
	if (GetSightRayHitLocation(outHitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *outHitLocation.operator/(100.f).ToString())
		GetControlledTank()->AimAt(outHitLocation);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *outHitLocation.operator/(100.f).ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	//find reticle position
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);
	FVector2D crosshairLocation;
	crosshairLocation.X = viewportSizeX * crosshairXLocation;
	crosshairLocation.Y = viewportSizeY * crosshairYLocation;
	
	//deproject screen to world
	FVector worldLocation, lookDirection;
	if (DeprojectScreenPositionToWorld(crosshairLocation.X, crosshairLocation.Y, worldLocation, lookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("world direction %s"), *lookDirection.ToString())
		//FVector startLocation = PlayerCameraManager->GetCameraLocation();
		FVector startLocation = worldLocation; //TODO see which one more accurate
		FVector endLocation = startLocation + lineTraceRange * lookDirection;
		return GetLookVectorHitLocation(startLocation, endLocation, outHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector startLocation, FVector endLocation, FVector &outHitLocation) const
{	
	FHitResult hit;	

	//line trace along look direction
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(GetPawn());
	//FCollisionResponseParams responseParams;
	if(GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, 
									ECollisionChannel::ECC_Visibility,
									queryParams))
		{
			outHitLocation = hit.Location;
			return true;
		}
	else {
		outHitLocation = FVector(0);
		//UE_LOG(LogTemp, Warning, TEXT("player line trace failed"))
		return false;
	}
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	auto aimComponent = tank->FindComponentByClass<UTankAimingComponent>();
	if(ensure(aimComponent))	FoundAimingComponent(aimComponent);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("player controller cannot find aim component"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}