/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#include "Modules/DoorStaticMesh.h"
#include "Components/SceneComponent.h"
#include "BaseDoor.h"
#include "Mechanics/BaseDoorMechanic.h"

UDoorStaticMesh::UDoorStaticMesh() : Super()
{
}

#pragma region Set&Get

	BaseDoorMechanic* UDoorStaticMesh::GetMechanic()
	{
		return (IsValid(MechanicDataAsset)) ? &Mechanic : nullptr;
	}

	void UDoorStaticMesh::SpawnPivot()
	{
		ABaseDoor* Door = Cast<ABaseDoor>(GetOwner());
		if (IsValid(Door))
		{
			Door->AddPivot(this);
		}
	}

#pragma endregion Set&Get

#pragma region ClassFunctions

	void UDoorStaticMesh::Initialize()
	{
		Mechanic = BaseDoorMechanic(this);
		if (GetMechanic())
		{
			this->GetMechanic()->SetMovableComponent(this->GetAttachParent());
			this->GetMechanic()->Initialize(MechanicDataAsset, bFlipTranslation);
		}
	}

#pragma endregion ClassFunctions

