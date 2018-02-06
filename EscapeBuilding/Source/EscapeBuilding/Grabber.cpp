// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
///Set functions
//Set up function used for action "Grab" is pressed
void UGrabber::PressGrab() {
	auto Hit = UGrabber::ReturnFirstPhysicsBodyInReach();
	auto ComponentToGrab = Hit.GetComponent();
	if (Hit.GetActor() != nullptr) {
		PhysicsHandle->GrabComponent(ComponentToGrab,
			NAME_None,
			Hit.GetActor()->GetActorLocation(),
			true);
	}
}
void UGrabber::ReleaseGrab() {
	PhysicsHandle->ReleaseComponent();
}
//Look for Physics handle component
void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("ERROR:PHYSICS HANDLE NOT FOUND"))
	}
}
void UGrabber::FindInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("ERROR:INPUT COMPONENT NOT FOUND"));
	}
}

const FHitResult UGrabber::ReturnFirstPhysicsBodyInReach() {
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetLineTraceStart(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return HitResult;
}
//get end of reach
const FVector UGrabber::GetLineTraceEnd() {
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	FVector EndTrace = ViewPointLocation + ViewPointRotation.Vector()*Reach;
	return EndTrace;
}
//get start of reach
const FVector UGrabber::GetLineTraceStart() {
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	return ViewPointLocation;
}
///End set functions

/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//Look for physics component and input component
	UGrabber::FindPhysicsHandleComponent();
	UGrabber::FindInputComponent();
	//key binding
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::PressGrab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseGrab);
}
///End begin play

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Moving grabbed AActor
	if (PhysicsHandle->GrabbedComponent) {
		//Get new location for the target
		FRotator TargetRotation;
		FVector TargetLocation;
		PhysicsHandle->GetTargetLocationAndRotation(TargetLocation, TargetRotation);
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
		PhysicsHandle->SetTargetRotation(FRotator(0.0,TargetRotation.Yaw,0.0));
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}