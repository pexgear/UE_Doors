/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "DoorMechanicDataAsset.h"

class DOORS_API BaseDoorMechanic
{
	
public:	
	BaseDoorMechanic() {};
	// Sets default values for this actor's properties
	BaseDoorMechanic(class UMeshComponent* Owner);

	virtual void Tick(float DeltaTime);

public:
	void Initialize(UDoorMechanicDataAsset* InMechanicDataAsset, const bool bFlipTranslation = false);

	void SetInitialPosition(const FVector& InPosition);

	const FVector* GetInitialPosition() const;

	void SetMovableComponent(class USceneComponent* InMovableComponent);

	class USceneComponent* GetMovableComponent() const;

	class UMeshComponent* GetMeshOwner() const;

	bool IsStillMoving();

	/** Starts the door movement */
	void Start();

	/** Stops the door movement */
	void Stop();
	
	void Reverse();

private:
	float GetNormalizedElapsedTime() const;

private:

	FVector InitialPosition;
	FVector FinalPosition;

	FRotator InitialRotation;
	FRotator FinalRotation;

	FVector LastPosition;
	FRotator LastRotation;

	mutable float ElapsedTime = 0.f;

	int8 TimeMultiplier = -1.f;
	
	bool bIsStillMoving = false;

	bool bFlipTranslation = false;

	UPROPERTY()
	class USceneComponent* MovableComponent;
		
	UPROPERTY()
	class UMeshComponent* MeshOwner;

	UPROPERTY(EditAnywhere)
	class UDoorMechanicDataAsset* MechanicDataAsset;
};
