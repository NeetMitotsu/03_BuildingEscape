// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grapper reporting for duty!!"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);


	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd, 
		FColor(255, 0, 0),
		false, 
		0.f, 
		0.f,
		10.f
	);

	// Log out to test
	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s, Position: %s"), 
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);*/
	//  

	// See what we hit

}

