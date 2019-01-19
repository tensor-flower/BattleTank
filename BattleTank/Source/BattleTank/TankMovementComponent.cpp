// Guo Wanqi 2019

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float verticalThrow) {
	//UE_LOG(LogTemp, Warning, TEXT("vertical throw %f"), verticalThrow);
	if (!leftTrack || !rightTrack) return;
	leftTrack->SetThrottle(verticalThrow);
	rightTrack->SetThrottle(verticalThrow);
}

void UTankMovementComponent::IntendTurnRight(float horizontalThrow) {
	if (!leftTrack || !rightTrack) return;
	leftTrack->SetThrottle(horizontalThrow);
	rightTrack->SetThrottle(-horizontalThrow);
}

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet) {
	if (!leftTrackToSet || !rightTrackToSet) return;
	leftTrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//FName name = GetOwner()->GetFName();
	FVector tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector moveVelocityNormal = MoveVelocity.GetSafeNormal();
	float angle = FVector::DotProduct(tankForward, moveVelocityNormal);
	//UE_LOG(LogTemp, Warning, TEXT("%s move velocity %s"), *name.ToString(), *MoveVelocity.GetSafeNormal().ToString())
	IntendMoveForward(angle);
}
