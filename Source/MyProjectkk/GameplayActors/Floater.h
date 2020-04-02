// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class MYPROJECTKK_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshComponents")
	UStaticMeshComponent* staticMesh;

	//Location used by setAcotrLocation when beginPlay() is called
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloaterVariables")
	FVector initLocation;

	// Location of the actor when dragged in from the editor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "FloaterVariables")
	FVector placedLocation; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FloaterVariables")
	bool bInitializeFloaterLocations;

	UPROPERTY(BlueprintReadOnly, Category = "FloaterVariables")
	FVector worldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FloaterVariables")
	FVector initialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariables")
	bool bShouldFloat;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="FloaterVariables")
	FVector initialForce;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "FloaterVariables")
	FVector initialTorque;

private:

	float runningTime;
	UPROPERTY(EditAnywhere, Category="FloaterVariables | WaveParameters")
	float amplitude; 
	UPROPERTY(EditAnywhere, Category = "FloaterVariables | WaveParameters")
	float frequency;
	UPROPERTY(EditAnywhere, Category = "FloaterVariables | WaveParameters")
	float C;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
