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
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State") EFiringStatus firingStatus = EFiringStatus::Aiming;
	UFUNCTION(BlueprintCallable, Category = "setup")
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);
public:	
	void AimComponentAim(FVector outHitLocation);
private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	void MoveBarrel(FRotator);
	void MoveTurret(FRotator);
	UPROPERTY(EditDefaultsOnly)float speed = 6000.f;
};
