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
