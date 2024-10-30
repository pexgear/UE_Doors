/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DoorEaseCurve.h"
#include "DoorMechanicDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DOORS_API UDoorMechanicDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere)
		FVector Movement;

		UPROPERTY(EditAnywhere)
		FRotator Rotation;

		UPROPERTY(EditAnywhere)
		UDoorEaseCurve* EaseCurve;

		UPROPERTY(EditAnywhere)
		float OpeningTime;

		float CachedCurveLength = -1;

};
