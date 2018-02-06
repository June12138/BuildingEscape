// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

//Get total mass on pressure plate
/*
float UOpenDoor::GetTotalMassOnPlate() {
	TArray <AActor*> ActorsOnPlate;
	float TotalMass = 0.0;
	PressurePlate->GetOverlappingActors(ActorsOnPlate);
	for (const auto& Actor : ActorsOnPlate){
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
*/
// Sets default values for this component's properties

bool UOpenDoor::CheckActorOnPlate() {
	TArray <AActor*> ActorsOnPlate;
	PressurePlate->GetOverlappingActors(ActorsOnPlate);
	for (const auto& Actor : ActorsOnPlate) {
			if (!Actor->GetName().Compare("SM_Statue_Blueprint_97")) {
				return true;
			}
			else {
				return false;
			}
	}
	return NULL;
}
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//see if the pressure plate overlap with actor that opens
	if (CheckActorOnPlate()) {
		OpenDoorRequest.Broadcast();
	}else{
		CloseDoorRequest.Broadcast();
	}
}