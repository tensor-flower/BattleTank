// Guo Wanqi 2019

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) {
	//UE_LOG(LogTemp, Warning, TEXT("%s %f throttle"), *GetName(), throttle)
	FVector force = GetForwardVector() * throttle * maxDrivingForce;
	FVector loaction = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(force, loaction);
}


