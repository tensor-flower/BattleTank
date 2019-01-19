// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
UCLASS()
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelRef(UTankBarrel*);
	void SetTurretRef(UTankTurret*);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State") EFiringStatus firingStatus = EFiringStatus::Reloading;

public:	
	void AimComponentAim(FVector outHitLocation, float speed);
private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	void MoveBarrel(FRotator);
	void MoveTurret(FRotator);

};
