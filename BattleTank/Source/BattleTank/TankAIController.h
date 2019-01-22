// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
private:
	float stoppingDistance = 2000.f;
	UTankAimingComponent* aimComponent = nullptr;
public:
	virtual void Tick(float DeltaTime) override;
};
