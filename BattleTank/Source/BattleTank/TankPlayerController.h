// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	UPROPERTY(Editanywhere) float crosshairXLocation = 0.5f;
	UPROPERTY(Editanywhere) float crosshairYLocation = 0.33333f;
	UPROPERTY(Editanywhere) int32 lineTraceRange = 1000000;
	bool GetLookVectorHitLocation(FVector, FVector, FVector&) const;

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
};
