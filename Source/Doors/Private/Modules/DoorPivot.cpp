/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#include "Modules/DoorPivot.h"

// Sets default values for this component's properties
UDoorPivot::UDoorPivot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorPivot::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDoorPivot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


#pragma region Set&Get

	void UDoorPivot::SetMeshOwner(class UMeshComponent* InMeshOwner)
	{
		if (ensure(!MeshOwner || MeshOwner == InMeshOwner))
		{
			MeshOwner = InMeshOwner;
		}
	}

#pragma endregion regionName
