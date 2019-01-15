// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float);
private:	
	UPROPERTY(Editanywhere, Category = Setup) float maxDegreesPerSecond = 5.f;
	UPROPERTY(Editanywhere, Category = Setup) float maxElevation = 30.f;
	UPROPERTY(Editanywhere, Category = Setup) float minElevation = 0.f;
};
