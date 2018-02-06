// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEBUILDING_API UGrabber : public UActorComponent
{
	GENERATED_BODY()
public:
	UGrabber();
	virtual void BeginPlay() override;
	//called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	// Sets default values for this component's properties
	float Reach = 150.0;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	//ray-cast and grab what's in reach
	void PressGrab();
	void ReleaseGrab();
	void FindPhysicsHandleComponent();
	void FindInputComponent();
	const FHitResult ReturnFirstPhysicsBodyInReach();
	const FVector GetLineTraceEnd();
	const FVector GetLineTraceStart();
};