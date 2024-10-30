/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#include "Mechanics/BaseDoorMechanic.h"
#include "Components/MeshComponent.h"
#include "Modules/DoorPivot.h"

BaseDoorMechanic::BaseDoorMechanic(UMeshComponent* Owner)
{
	InitialPosition = FVector::ZeroVector;
	FinalPosition = FVector::ZeroVector;

	InitialRotation = FRotator::ZeroRotator;
	FinalRotation = FRotator::ZeroRotator;

	LastPosition = FVector::ZeroVector;
	LastRotation = FRotator::ZeroRotator;

	this->MeshOwner = Owner;
}

void BaseDoorMechanic::Tick(float DeltaTime)
{
	if (!MechanicDataAsset || !bIsStillMoving)
	{
		return;
	}

	this->ElapsedTime += TimeMultiplier * DeltaTime;

	bIsStillMoving = false;

	float alphaValue = GetNormalizedElapsedTime();
	if (MechanicDataAsset->EaseCurve)
	{
		float min, max;
		MechanicDataAsset->EaseCurve->GetTimeRange(min, max);
		alphaValue = MechanicDataAsset->EaseCurve->GetFloatValue(min + (max - min) * alphaValue);
		MechanicDataAsset->EaseCurve->GetValueRange(min, max);
		alphaValue = FMath::Clamp((alphaValue - min) / (max - min), 0.f, 1.f);
	}
	if (MechanicDataAsset->Movement != FVector::ZeroVector)
	{
		MovableComponent->SetRelativeLocation(FMath::Lerp(InitialPosition, FinalPosition, alphaValue));
	}
	if (MechanicDataAsset->Rotation != FRotator::ZeroRotator)
	{
		MovableComponent->SetRelativeRotation(FMath::LerpRange(InitialRotation, FinalRotation, alphaValue));
	}
	
	if (GetMovableComponent()->GetComponentLocation() != LastPosition)
	{
		bIsStillMoving = true;
		LastPosition = GetMovableComponent()->GetComponentLocation();
	}
	if (GetMovableComponent()->GetComponentRotation() != LastRotation)
	{
		bIsStillMoving = true;
		LastRotation = GetMovableComponent()->GetComponentRotation();
	}
}

void BaseDoorMechanic::Initialize(UDoorMechanicDataAsset* InMechanicDataAsset, const bool bInFlipTranslation)
{
	MechanicDataAsset = InMechanicDataAsset;

	if (MechanicDataAsset)
	{
		this->bFlipTranslation = bInFlipTranslation;

		int multiplier = this->bFlipTranslation ? -1 : 1;
		FinalPosition = InitialPosition + (InMechanicDataAsset->Movement * multiplier);
		FinalRotation = InitialRotation + (InMechanicDataAsset->Rotation * multiplier);
	}
}

#pragma region Set&Get

	void BaseDoorMechanic::SetInitialPosition(const FVector& InPosition)
	{
		this->InitialPosition = InPosition;
	}

	const FVector* BaseDoorMechanic::GetInitialPosition() const
	{
		return &this->InitialPosition;
	}

	void BaseDoorMechanic::SetMovableComponent(class USceneComponent* InMovableComponent)
	{
		if (UDoorPivot* Pivot = Cast<UDoorPivot>(InMovableComponent))
		{
			this->SetInitialPosition(Pivot->GetRelativeTransform().GetLocation());
			this->MovableComponent = Pivot;
			Pivot->SetMeshOwner(this->GetMeshOwner());
		}
		else
		{
			this->SetInitialPosition(this->GetMeshOwner()->GetRelativeTransform().GetLocation());
			this->MovableComponent = this->GetMeshOwner();
		}
	}

	USceneComponent* BaseDoorMechanic::GetMovableComponent() const
	{
		return this->MovableComponent;
	}

	UMeshComponent* BaseDoorMechanic::GetMeshOwner() const
	{
		return this->MeshOwner;
	}

	bool BaseDoorMechanic::IsStillMoving()
	{
		return bIsStillMoving;
	}

#pragma endregion Set&Get

	void BaseDoorMechanic::Start()
	{
		if (bIsStillMoving || GetNormalizedElapsedTime() == 0 || GetNormalizedElapsedTime() == 1)
		{
			Reverse();
		}
		else
		{
			bIsStillMoving = true;
		}
	}

	void BaseDoorMechanic::Stop()
	{
		bIsStillMoving = false;
	}

	void BaseDoorMechanic::Reverse()
	{
		TimeMultiplier *= -1;
		bIsStillMoving = true;
	}

	float BaseDoorMechanic::GetNormalizedElapsedTime() const
	{
		ElapsedTime = FMath::Clamp(ElapsedTime, 0.f, MechanicDataAsset->OpeningTime);
		return FMath::Clamp(this->ElapsedTime / MechanicDataAsset->OpeningTime, 0.f, 1.f);
	}