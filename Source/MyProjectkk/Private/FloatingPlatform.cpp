// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"


// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	StartPoint = FVector(0.0f);
	EndPoint = FVector(0.0f);
	interSpeed = 2.0f;
	bInterping = false;
	interpTime = 1.0f;
	

}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartPoint = GetActorLocation();
	EndPoint += StartPoint;  //Endpoint on 
	DistanceStartToEnd = (EndPoint - StartPoint).Size(); 
	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, interpTime);

}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bInterping) {

		FVector CurrentLocation = GetActorLocation();
		FVector Interp = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, interSpeed);
		SetActorLocation(Interp);

		float DistanceTraveled = (GetActorLocation() - StartPoint).Size();
		if (DistanceStartToEnd - DistanceTraveled <= 1.0f)
		{
			ToggleInterping();
			GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterping, interpTime);
			SwapVectors(StartPoint, EndPoint);
		}

	} 
}

void AFloatingPlatform::ToggleInterping()
{
	//toggle
	bInterping = !bInterping;
}

void AFloatingPlatform::SwapVectors(FVector& vecA, FVector& vecB)
{
	FVector temp = vecA;
	vecA = vecB;
	vecB = temp;
}

