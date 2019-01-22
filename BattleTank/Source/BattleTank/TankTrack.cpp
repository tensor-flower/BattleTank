// Guo Wanqi 2019

#include "TankTrack.h"
#include "Components/StaticMeshComponent.h"

void UTankTrack::SetThrottle(float throttle) {
	//UE_LOG(LogTemp, Warning, TEXT("%s %f throttle"), *GetName(), throttle)
	FVector force = GetForwardVector() * throttle * maxDrivingForce;
	FVector loaction = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(force, loaction);
}

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto acc = -slippageSpeed / DeltaTime * GetRightVector();
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto friction = tankRoot->GetMass() * acc / 2;
	tankRoot->AddForce(friction);
}