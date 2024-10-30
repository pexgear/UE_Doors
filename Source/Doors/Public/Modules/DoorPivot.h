/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseGizmos/GizmoArrowComponent.h"
#include "DoorPivot.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DOORS_API UDoorPivot : public UGizmoArrowComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorPivot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Set&Get

	public:
		void SetMeshOwner(class UMeshComponent* InMeshOwner);

#pragma endregion regionName

#pragma region ClassVariables

	private:
		UMeshComponent* MeshOwner;

#pragma region ClassVariables

	

#pragma endregion ClassVariables

};
