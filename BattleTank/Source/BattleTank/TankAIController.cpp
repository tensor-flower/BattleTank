// Guo Wanqi 2019

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (!tank) {
		UE_LOG(LogTemp, Error, TEXT("pawn not possessed by AI"))
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("pawn possessed by AI %s"), *tank->GetFName().ToString());

	ATank* playerTank = GetPlayerControlledTank();
	if (!playerTank)
		UE_LOG(LogTemp, Error, TEXT("AI cannot find player tank"))
	else
		UE_LOG(LogTemp, Warning, TEXT("AI found player tank %s"), *playerTank->GetFName().ToString());
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowards()
{
	GetControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());
}

void ATankAIController::Tick(float DeltaTime)
{
	AimTowards();
}
