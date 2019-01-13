// Guo Wanqi 2019

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	APawn* tank = GetPawn();
	if (!tank)
	{
		UE_LOG(LogTemp, Error, TEXT("pawn not possessed by player"))
		return nullptr;
	}
	FName pawnName = tank->GetFName();
	UE_LOG(LogTemp, Warning, TEXT("%s possessed by player"), *pawnName.ToString())
	return Cast<ATank>(tank);
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
}

