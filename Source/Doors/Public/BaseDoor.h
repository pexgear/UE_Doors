/** Copyright © 2021 by Giuseppe Genna. All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Modules/DoorPivot.h"
#include "BaseDoor.generated.h"

UENUM()
enum class EDoorStatus : uint8
{
	Closed,
	Opening,
	Opened,
	Closing
};

UCLASS(Abstract)
class DOORS_API ABaseDoor : public AActor
{
	GENERATED_BODY()

#pragma region OverrodeFunctions

	public:	
		// Sets default values for this actor's properties
		ABaseDoor();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		virtual void PostInitializeComponents() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

#pragma endregion OverrodeFunctions

#pragma region ClassFunctions

	public:
		/** Called to open the door using the mechanic */
		UFUNCTION(BlueprintCallable)
		void Open();

		/** Called to close the door using the mechanic */
		UFUNCTION(BlueprintCallable)
		void Close();

		/** Called to open or close the door, depending
		 *	on the current status,  using the mechanic */
		UFUNCTION(BlueprintCallable)
		void Toggle();

#if WITH_EDITOR
		void AddPivot(class UDoorStaticMesh* DoorMesh);
#endif
	
	protected:
		/** To override specifing what opening condition, if present */
		virtual bool OpenedCondition() { return false; };

		/** To override specifing what closing condition, if present */
		virtual bool ClosedCondition() { return false; };

	private:
		void UpdateStatus();

#pragma endregion ClassFunctions

#pragma region Set&Get

	public:
		/** Tells if the door is opened, closed or opening, closing */
		EDoorStatus GetDoorStatus() const { return Status; };

	protected:
		void SetDoorStatus(const EDoorStatus InStatus);

#pragma endregion Set&Get

#pragma region ClassVars
	public:
		UPROPERTY(EditAnywhere)
		UDoorPivot* Pivot;

	protected:
		UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
		bool bKeepTickEnabled = false;

	private:
		/** List of mechanics to use for the door */
		TArray<class BaseDoorMechanic*> Mechanics;

		UPROPERTY()
		EDoorStatus Status;

		/** Last valid status before the actual,
		 *	used for comparations with the new one*/
		UPROPERTY()
		EDoorStatus LastStatus;


#pragma endregion ClassVars

};

UCLASS()
class DOORS_API ADoor : public ABaseDoor
{
	GENERATED_BODY()

#pragma region OverrodeFunctions
	public:
		ADoor();
#pragma endregion OverrodeFunctions

#pragma region ClassVars
	protected:
		UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
		class UDoorStaticMesh* DoorMesh;

#pragma endregion ClassVars

};