// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
//class UTankMovementComponent;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly) UTankAimingComponent* tankAimingComponent = nullptr;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) 
	//UTankMovementComponent* tankMovementComponent = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AimAt(FVector);

	UFUNCTION(BlueprintCallable)
	void Fire();
private:
	UTankBarrel* barrel = nullptr; //to spawn projectile
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float launchSpeed = 4000.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup") TSubclassOf<AProjectile> projectileBP;
	UPROPERTY(EditDefaultsOnly, Category = "Firing") float cooldownTimeInSeconds = 3.f;
	double lastFireTime = 0;
};
