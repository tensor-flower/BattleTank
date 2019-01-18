// Guo Wanqi 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
class UTankTrack;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float verticalThrow);
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(float horizontalThrow);

	UFUNCTION(BlueprintCallable, Category = setup)
	void Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);
private:
	UTankTrack* leftTrack = nullptr;
	UTankTrack* rightTrack = nullptr;
};
