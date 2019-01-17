// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
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
	UTankAimingComponent* tankAimingComponent = nullptr;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector);
	UFUNCTION(BlueprintCallable, Category = Setup)
	//void SetBarrelRef(UStaticMeshComponent* barrelRef);
	void SetBarrelRef(UTankBarrel* barrelRef);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretRef(UTankTurret* turretRef);
private:
	//UStaticMeshComponent* barrelRef;
	UTankBarrel* barrelRef;
	UTankTurret* turretRef;
	UPROPERTY(Editanywhere, Category=Firing) float launchSpeed = 5000.f;
};
