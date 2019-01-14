// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
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
	ATank* GetControlledTank () const;
	ATank* GetPlayerControlledTank() const;
	void AimTowards();
public:
	virtual void Tick(float DeltaTime) override;
};
