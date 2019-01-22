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
class AProjectile;
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
	void AimComponentAim(FVector);
	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	//methods
	void MoveBarrel(FRotator);
	void MoveTurret(FRotator);
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	bool IsBarrelMoving();
	//pointers and refs
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	FVector aimDirection;

	//config params
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float speed = 6000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup") TSubclassOf<AProjectile> projectileBP;
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float cooldownTimeInSeconds = 3.f;
	double lastFireTime = 0;
};