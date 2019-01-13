// Guo Wanqi 2019

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (!tank)
		UE_LOG(LogTemp, Error, TEXT("pawn not possessed by AI"))
	UE_LOG(LogTemp, Warning, TEXT("pawn possessed by AI %s"), *tank->GetFName().ToString());
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
