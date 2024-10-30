/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#include "BaseDoor.h"
#include "Components/SceneComponent.h"
#include "Modules/DoorPivot.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Modules/DoorStaticMesh.h"
#include "Mechanics/BaseDoorMechanic.h"

#pragma endregion OverrodeFunctions

	// Sets default values
	ABaseDoor::ABaseDoor()
	{
 		// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;

		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	}

	// Called when the game starts or when spawned
	void ABaseDoor::BeginPlay()
	{
		Super::BeginPlay();
	
	}

	void ABaseDoor::PostInitializeComponents()
	{
		Super::PostInitializeComponents();

		TArray<UActorComponent*> StaticMeshComponents = GetComponentsByClass(UDoorStaticMesh::StaticClass());

		for (UActorComponent* SingleMeshComponent : StaticMeshComponents)
		{
			UDoorStaticMesh* Mesh = Cast<UDoorStaticMesh>(SingleMeshComponent);
			if (Mesh)
			{
				Mesh->Initialize();
				if (BaseDoorMechanic* MeshMechanic = Mesh->GetMechanic())
				{
					Mechanics.Add(MeshMechanic);
				}
			}
		}
	}

	// Called every frame
	void ABaseDoor::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

		for (BaseDoorMechanic* Mech : Mechanics)
		{
			if (/*Mech->GetMeshOwner() check if it movable && */ Mech->IsStillMoving() || LastStatus != GetDoorStatus())
			{
				Mech->Tick(DeltaTime);
			}
		}

		UpdateStatus();
	}

#pragma endregion OverrodeFunctions

#pragma region ClassFunctions

	void ABaseDoor::Open()
	{
		switch (GetDoorStatus())
		{
			case EDoorStatus::Closed:	//Fallthrough
				SetActorTickEnabled(true);
			case EDoorStatus::Closing:
				SetDoorStatus(EDoorStatus::Opening);
				break;
			default:
				break;
		}
	}

	void ABaseDoor::Close()
	{
		switch (GetDoorStatus())
		{
			case EDoorStatus::Opened:	//Fallthrough
				SetActorTickEnabled(true);
			case EDoorStatus::Opening:
				SetDoorStatus(EDoorStatus::Closing);
				break;
			default:
				break;
		}
	}

	void ABaseDoor::Toggle()
	{
		switch (GetDoorStatus())
		{
			case EDoorStatus::Closed:	//Fallthrough
			case EDoorStatus::Closing:
				Open();
				break;
			case EDoorStatus::Opened:	//Fallthrough
			case EDoorStatus::Opening:
				Close();
				break;
			default:
				break;
		}
	}

#if WITH_EDITOR
	void ABaseDoor::AddPivot(UDoorStaticMesh* DoorMesh)
	{
		if (!IsValid(DoorMesh) || DoorMesh->GetOwner() != this)
		{
			return;
		}
		FName PivotName = FName(*FString("Pivot_") + (DoorMesh->GetFName().ToString()));
		Pivot = NewObject<UDoorPivot>(this, PivotName);
		
		USceneComponent* ParentComp = DoorMesh->GetAttachParent();
		if (IsValid(ParentComp))
		{
			Pivot->AttachToComponent(ParentComp, FAttachmentTransformRules::KeepRelativeTransform);
			Pivot->SetRelativeLocation(DoorMesh->GetRelativeLocation());
		}
		Pivot->RegisterComponent();
		DoorMesh->AttachToComponent(Pivot, FAttachmentTransformRules::KeepRelativeTransform);
		DoorMesh->SetRelativeLocation(FVector::ZeroVector);
	}
#endif

	void ABaseDoor::UpdateStatus()
	{
		switch (GetDoorStatus())
		{
			case EDoorStatus::Closed:	//Fallthrough
			case EDoorStatus::Opened:	
				SetActorTickEnabled(false || bKeepTickEnabled);
				break;
			case EDoorStatus::Closing:
				if(ClosedCondition()) 
				{
					SetDoorStatus(EDoorStatus::Closed);
					SetActorTickEnabled(false || bKeepTickEnabled);

				}
				break;
			case EDoorStatus::Opening:
				if (OpenedCondition())
				{
					SetDoorStatus(EDoorStatus::Opened);
					SetActorTickEnabled(false || bKeepTickEnabled);
				}
				break;
		}
	}
	   
	void ABaseDoor::SetDoorStatus(const EDoorStatus InStatus)
	{
			LastStatus = Status; 
			Status = InStatus;

			if (LastStatus != Status)
			{
				for (BaseDoorMechanic* Mech : Mechanics)
				{
					if (InStatus == EDoorStatus::Closing || InStatus == EDoorStatus::Opening)
					{
						if (/*Mech->GetMeshOwner() check if it movable && */ Mech->IsStillMoving() || LastStatus != GetDoorStatus())
						{
							Mech->Start();
						}
					}
				}
			}
	}

#pragma endregion ClassFunctions


#pragma region OverrodeFunctions
	ADoor::ADoor() {
		DoorMesh = CreateDefaultSubobject<UDoorStaticMesh>(TEXT("MainDoorMesh"));
		DoorMesh->SetupAttachment(RootComponent);
	}
#pragma endregion OverrodeFunctions