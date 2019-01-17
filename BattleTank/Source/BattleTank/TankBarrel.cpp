// Guo Wanqi 2019

#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	//UE_LOG(LogTemp, Warning, TEXT("%f relative speed"), relativeSpeed)
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewRotation = RelativeRotation.Pitch + elevationChange;
	auto newRotation = FMath::Clamp(rawNewRotation, minElevation, maxElevation);
	SetRelativeRotation(FRotator(newRotation, 0, 0));
}



