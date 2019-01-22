// Guo Wanqi 2019

#include "TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	aimComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimComponent))	return;
}

void ATankAIController::Tick(float DeltaTime)
{
	auto tank = GetPawn();
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(tank) || !ensure(playerTank)) return;
	MoveToActor(playerTank, stoppingDistance);
	if (!ensure(aimComponent))	return;
	aimComponent->AimComponentAim(playerTank->GetActorLocation());
	aimComponent->Fire();
}
