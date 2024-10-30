/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Mechanics/BaseDoorMechanic.h"
#include "Mechanics/DoorMechanicDataAsset.h"
#include "DoorStaticMesh.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class DOORS_API UDoorStaticMesh : public UStaticMeshComponent
{
	GENERATED_BODY()

	public:
		UDoorStaticMesh();

#pragma region ClassFunctions

	public:
		void Initialize();

#pragma endregion ClassFunctions

#pragma region Set&Get

	public:
		class BaseDoorMechanic* GetMechanic();

		UFUNCTION(BlueprintCallable, CallInEditor)
		void SpawnPivot();
#pragma endregion Set&Get

#pragma region ClassVariables

	protected:
		UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		bool bFlipTranslation;

		BaseDoorMechanic Mechanic;

		UPROPERTY(EditAnywhere)
		UDoorMechanicDataAsset* MechanicDataAsset;



#pragma region ClassVariables
};
