// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Createdefaultobject luo uuden objekti
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));
	worldOrigin = FVector(0.0f);
	initLocation = FVector(0.0f);
	placedLocation = FVector(0.0f);

	initialDirection = FVector(0.0f);

	bShouldFloat = false;
	bInitializeFloaterLocations = false;
	initialForce = FVector(2000000.0f, 0.0f, 0.0f);
	initialTorque = FVector(2000000.0f, 0.0f, 0.0f);

	amplitude = 1.0;
	frequency = 1.0;
	C = 1.0;
	runningTime = 0.0f;

}
   
// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	//float initialX = FMath::FRandRange(-1.0f,1.0f); //0 - 1
	//float initialY = FMath::FRandRange(-1.0f,1.0f);
	//float initialZ = FMath::FRandRange(-1.0f,1.0f);
	//float scale = 4.0f;
	//initialDirection = FVector(initialX*scale, initialY*scale, initialZ*scale);

	placedLocation = GetActorLocation();

	if (bInitializeFloaterLocations) {
		SetActorLocation(initLocation);
	}
	FHitResult hitResult;
	staticMesh->AddForce(initialForce);
	staticMesh->AddTorque(initialTorque);

	// Pitch, yaw, roll
	// Pitch nostaa nokkaa ylˆs tai alas
	// Yaw k‰‰nt‰‰ sivuille (katsoo)
	// Roll k‰‰nt‰‰ akselin ymp‰rill‰, (meno suuntaan) 
	//FRotator rotation = FRotator(0.0f, 0.0f, 30.0f);
	//AddActorLocalRotation(rotation);

	//AddActorWorldOffset(localOffset, true, &hitResult);
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat) {
	
		FVector newLocation = GetActorLocation();
		newLocation.Z = newLocation.Z + amplitude*FMath::Sin(frequency*2*PI*runningTime) + C;
		SetActorLocation(newLocation);
		runningTime += DeltaTime;
	//	FVector HitLocation = hitResult.Location;
	//	UE_LOG(LogTemp, Warning, TEXT("Hit Location x = %f, y = %f, z = %f"), HitLocation.X, HitLocation.Y, HitLocation.Z);
	}

	//FORCES: Rotation
	// Torque == spinning force

	//FRotator rotation = FRotator(1.0f, 0.0f, 0.0f);
	//AddActorWorldRotation(rotation);

}

