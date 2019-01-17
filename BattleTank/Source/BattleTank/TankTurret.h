// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void TurretYaw(float);
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup) float maxDegreesPerSecond = 30.f;
};
