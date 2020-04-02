// Fill out your copyright notice in the Description page of Project Settings.


#include "Critter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ACritter::ACritter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//setup attachments
	MeshComponent->SetupAttachment(GetRootComponent()); //addaa meshcomponentit root comppiin
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(-300.f, 0.f, 300.f));
	Camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	currentVelocity = FVector(0.0f);
	MaxSpeed = 100.0f;
}

// Called when the game starts or when spawned
void ACritter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector newLocation = GetActorLocation() + (currentVelocity * DeltaTime);
	SetActorLocation(newLocation);

}

// Called to bind functionality to input
void ACritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACritter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACritter::MoveRight);



}


void ACritter::MoveForward(float value) {
	//clamp rajoittaa boundeihin
	currentVelocity.X = FMath::Clamp(value, -1.0f, 1.0f) * MaxSpeed;
}

void ACritter::MoveRight(float value) {
	currentVelocity.Y = FMath::Clamp(value, -1.0f, 1.0f) * MaxSpeed;
}
