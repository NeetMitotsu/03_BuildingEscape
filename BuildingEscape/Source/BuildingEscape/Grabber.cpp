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
	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attaching 
		//move the object that we're hoding 
}

// look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent() {	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		// Physics Hanle is found
	} else {
		UE_LOG(LogTemp, Error, TEXT(" missing physics handle component"));
	}
}

// Look for attached Input Component ( only appears at run time)
void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component found"));
		// bind th input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		UE_LOG(LogTemp, Error, TEXT(" missing physics handle component"));
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab() is calling"));

	/// LINE TRACE and see if we reach any actors with physics body collision channel set 
	GetFirstPhysicsBodyInReach();

	// if we hit something then attach a physics handle
		// TODO attach physics handle
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release() is calling"));
	// TODO release physics handle
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
	// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);


	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//  Line-trance (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trance hit : %s"), *(ActorHit->GetName()));
	}
	
	return Hit;
}

