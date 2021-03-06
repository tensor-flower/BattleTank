// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class ATank;
class UTankAimingComponent;
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
	UTankAimingComponent* aimComponent = nullptr;
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimCompRef);
public:
	virtual void Tick(float DeltaTime) override;
};
