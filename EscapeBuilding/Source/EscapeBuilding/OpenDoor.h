// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEBUILDING_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UOpenDoor();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	bool CheckActorOnPlate();
	UPROPERTY(VisibleAnywhere)
		float DoorOpen = 90.0;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.5;
	//float GetTotalMassOnPlate();
	UPROPERTY(EditAnywhere)
		float TriggerMass = 50.f;
	//declare FEvent
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEvent);
	//set open door and close door events
	UPROPERTY(BlueprintAssignable)
		FEvent OpenDoorRequest;
	UPROPERTY(BlueprintAssignable)
		FEvent CloseDoorRequest;
};
