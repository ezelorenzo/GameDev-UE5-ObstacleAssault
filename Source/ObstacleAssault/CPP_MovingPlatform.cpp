// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MovingPlatform.h"

// Sets default values
ACPP_MovingPlatform::ACPP_MovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

}

// Called when the game starts or when spawned
void ACPP_MovingPlatform::BeginPlay()
{
	Super::BeginPlay();		
	
	StartLocation = GetActorLocation();

	//FString myString = "My String Value";

	//FString name = GetName();
	//
	//UE_LOG(LogTemp, Display, TEXT("Here's My Name: %s"), *name); //when we do a %s I need a "*"  in de value. Pointers

	//UE_LOG(LogTemp, Display, TEXT("Here's My String: %s"), *myString); //when we do a %s I need a "*"  in de value. Pointers

	UE_LOG(LogTemp, Display, TEXT("Configured moved distance: %f"), MoveDistance);
	
}

// Called every frame
void ACPP_MovingPlatform::Tick(float DeltaTime)//scope resolution operator
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
}

void ACPP_MovingPlatform::MovePlatform(float DeltaTime)
{
	
	//Send platform back if gone too far
	//check how far we've moved
	if (ShouldPlatformReturn())
	{		
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + (MoveDirection * MoveDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		//Move platform forwards
	//Get current location
		FVector CurrentLocation = GetActorLocation();
		//Add vector to that location
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		//Set the location
		SetActorLocation(CurrentLocation);
	}
}

bool ACPP_MovingPlatform::ShouldPlatformReturn() const
{
	//MoveDistance = 200; //if i do this i cant compile because the function is const, I cant set anything in const.
	//reverse direction of motion if gone too far
	return GetDistanceMoved() > MoveDistance;
}

float ACPP_MovingPlatform::GetDistanceMoved() const
{
	return  FVector::Dist(StartLocation, GetActorLocation());
}

void ACPP_MovingPlatform::RotatePlatform(float DeltaTime)
{ 	
	/*FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	SetActorRotation(CurrentRotation);*/ // this can be replaced with the code below which is better.
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

