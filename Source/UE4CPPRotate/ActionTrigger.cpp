// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionTrigger.h"
#include "Engine/GameEngine.h" //Needed for Debug Messages
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UActionTrigger::UActionTrigger()
{
	PrimaryComponentTick.bCanEverTick = false; //Dont need to tick
}

// Called when the game starts
void UActionTrigger::BeginPlay()
{
	Super::BeginPlay();
	AActor* ParentActor = GetOwner();
	if (IsValid(ParentActor)) 
	{
		auto BoxComponent = Cast<UBoxComponent>(ParentActor->GetComponentByClass(UBoxComponent::StaticClass())); //Find BoxCollider on Parent
		if (IsValid(BoxComponent))	//Check we have one
		{
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UActionTrigger::BeginOverlap); //Attach the collision Handler
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot find BoxComponent Actor"));
		}
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find parent Actor"));
	}
}

void UActionTrigger::BeginOverlap(UPrimitiveComponent * OverlappedComponent
	, AActor * OtherActor
	, UPrimitiveComponent * OtherComp
	, int32 OtherBodyIndex
	, bool bFromSweep
	, const FHitResult & SweepResult)
{
	if (ActionActors.Num() > 0) 
	{
		for (int i = 0; i < ActionActors.Num(); i++)  //Step through linked actors
		{
			ActionActors[i]->NextRotation();	//Call Next rotation on all Linked Action Actors
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Action Actors attached"));
	}
}

