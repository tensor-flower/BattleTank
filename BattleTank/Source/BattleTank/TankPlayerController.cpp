// Guo Wanqi 2019

#include "TankPlayerController.h"
#include "Engine/World.h"

ATank* ATankPlayerController::GetControlledTank() const {
	APawn* tank = GetPawn();
	if (!tank)
	{
		UE_LOG(LogTemp, Error, TEXT("pawn not possessed by player"))
		return nullptr;
	}
	FName pawnName = tank->GetFName();
	//UE_LOG(LogTemp, Warning, TEXT("%s possessed by player"), *pawnName.ToString())
	return Cast<ATank>(tank);
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector outHitLocation;
	if (GetSightRayHitLocation(outHitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *outHitLocation.operator/(100.f).ToString())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *outHitLocation.operator/(100.f).ToString())
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
	//FCollisionQueryParams queryParams(FName(TEXT("")), true, this);
	//FCollisionResponseParams responseParams;
	if(GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, 
									ECollisionChannel::ECC_Visibility))
		{
			outHitLocation = hit.Location;
			return true;
		}
	else {
		outHitLocation = FVector(0);
		return false;
	}
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}