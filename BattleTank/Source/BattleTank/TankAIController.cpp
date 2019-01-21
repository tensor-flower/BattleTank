// Guo Wanqi 2019

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	ATank* tank = Cast<ATank>(GetPawn());
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(tank) || !ensure(playerTank)) return;
	MoveToActor(playerTank, stoppingDistance);
	tank->AimAt(playerTank->GetActorLocation());
	tank->Fire();
}
