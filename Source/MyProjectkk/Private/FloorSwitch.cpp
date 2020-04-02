// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"


// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	//Collision parameters
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); //not fire when it collides with anything
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());

	closeTime = 1.0f;
	bCharacterOnSwitch = false;

	//Delegate binds a function to event and call the function on event
}

void AFloorSwitch::CloseDoor()
{
	if (!bCharacterOnSwitch) {
		LowerDoor();
		RaiseDoorSwitch();
	}

}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();
	InitialSwitchLocation = FloorSwitch->GetComponentLocation();
	InitialDoorLocation = Door->GetComponentLocation();


	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapBegin); //Binding for event and func call
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapEnd);

	
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap begin"));
	if (!bCharacterOnSwitch) {
		bCharacterOnSwitch = true;
	}
	RaiseDoor();
	LowerDoorSwitch();

}

void AFloorSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap END"));

	if (bCharacterOnSwitch) {
		bCharacterOnSwitch = false;
		GetWorldTimerManager().SetTimer(SwitchHandle, this, &AFloorSwitch::CloseDoor, closeTime);
	}

	
}

void AFloorSwitch::UpdateDoorLocation(float Z)
{
	FVector newLocation = InitialDoorLocation;
	newLocation.Z += Z;

	Door->SetWorldLocation(newLocation);
}


void AFloorSwitch::UpdateSwitchLocation(float Z)
{
	FVector newLocation = InitialSwitchLocation;
	newLocation.Z += Z;

	FloorSwitch->SetWorldLocation(newLocation);
}
