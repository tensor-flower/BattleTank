// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
private:
	float stoppingDistance = 3000.f;
public:
	virtual void Tick(float DeltaTime) override;
};
