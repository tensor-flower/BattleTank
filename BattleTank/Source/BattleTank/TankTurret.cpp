// Guo Wanqi 2019

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::TurretYaw(float relativeSpeed) {
	//UE_LOG(LogTemp, Warning, TEXT("%f yaw"), relativeSpeed)
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto yawChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newRotation = RelativeRotation.Yaw + yawChange;
	//auto newRotation = FMath::Clamp(rawNewRotation, minElevation, maxElevation);
	SetRelativeRotation(FRotator(0, newRotation, 0));
}


