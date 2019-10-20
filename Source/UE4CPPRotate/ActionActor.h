// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionActor.generated.h"

UCLASS()
class UE4CPPROTATE_API AActionActor : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AActionActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category=Control)
	void SetRotate(bool doRotate);

	//Go to next rotation
	UFUNCTION(BlueprintCallable, Category = Control)
	bool NextRotation();

	//Go Reset to first rotation
	UFUNCTION(BlueprintCallable, Category = Control)
	bool ResetRotation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Custom)
	TArray<FRotator>	RotateValues;

private:
	bool	doRotationFlag = false;	//Should we be rotating flag

	int		CurrentStep = 0;	//Current Step in rotation array


	int		NextIndex();	//Get Next Index but loop at end of array

	FRotator	FromRotation; //Start of LERP
	FRotator	ToRotation;		//End of LERP
	float	CurrentLERP = 0.0;	//Where we are within the step 0.0 = start 1.0 = end 

};
