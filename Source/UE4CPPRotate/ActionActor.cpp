// Fill out your copyright notice in the Description page of Project Settings.
#include "ActionActor.h"
#include "Engine/GameEngine.h" //Needed for Debug Messages

// Sets default values
AActionActor::AActionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AActionActor::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AActionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Call parent update
	if (doRotationFlag) //Only rotate if rotate flag is set
	{
		if (RotateValues.Num() > 0) //make sure array is valid
		{
			FRotator CurrentRotation = FMath::Lerp(FromRotation, ToRotation, CurrentLERP); //Get Current rotation
			SetActorRotation(CurrentRotation, ETeleportType::None);
			CurrentLERP += DeltaTime;
			if (CurrentLERP >= 1.0) //Are we at the end
			{
				doRotationFlag = false; //Stop
				SetActorRotation(ToRotation, ETeleportType::None); //Make sure last rotation is actual Rotation stop
			}
		}
	}
}

bool AActionActor::NextRotation()
{
	if (RotateValues.Num() > 1) //Can only do next if array has two values
	{
		if (!doRotationFlag) //Are we busy
		{
			CurrentLERP = 0.0;		//Reset Current Step & LERP
			FromRotation = RotateValues[CurrentStep]; //Set new from rotation
			int NextStep = NextIndex();		//Next Index with looping
			ToRotation = RotateValues[NextStep];	
			CurrentStep = NextStep;
			doRotationFlag = true;	//Set Rotating
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Rotate Busy with last rotation"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("RotateValues[] needs to contain at least 2 values"));
	}
	return	false;
}

bool AActionActor::ResetRotation()
{
	if (RotateValues.Num() > 0)
	{
		CurrentLERP = 0.0;		//Reset Current Step & LERP
		CurrentStep = 0;
		FromRotation = GetActorRotation();
		ToRotation = RotateValues[CurrentStep]; //Starting position
		doRotationFlag = true;	//Set Rotating
		return	true;
	}
	UE_LOG(LogTemp, Error, TEXT("RotateValues[] is empty"));
	return	false;
}

int AActionActor::NextIndex()
{
	if (RotateValues.Num() > 1) 
	{
		return (CurrentStep + 1) % RotateValues.Num();	//This will loop the array
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("RotateValues[] needs to contain at least 2 values"));
		return 0;
	}
}

void AActionActor::SetRotate(bool doRotate)
{
	doRotationFlag = doRotate; //Set RotateFlag based on input
	if (GEngine) //Only in Debug build
	{
		UE_LOG(LogTemp, Warning, TEXT("New State %d"), doRotationFlag); //Output to Debug Log
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("New State %d"), doRotationFlag)); //Show on screen
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GEngine is NULL"));
	}
}
