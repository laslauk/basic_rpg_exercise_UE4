// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMain::AMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera boom (pulls towards the player if theres a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f; //camera follows the distance
	CameraBoom->bUsePawnControlRotation = true; //rotate arm based on the controller

	//Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleSize(110.0f, 44.0f);

	//Create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; //only follow boom, not controller character, boom adjusts to match the controller orientation

	BaseTurnRate = 65.f;
	BaseLoopUpRate = 65.f;

	//Dont rotate when the controller rotates
	//let that just affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//config character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; //automatically face direction character is moving, moves in the direction of input ..
	GetCharacterMovement()->RotationRate = FRotator(0.04f, 840.f, 0.0f); //.. at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->AirControl = 0.3f;


	MaxHealth = 100;
	Health = 77;
	MaxStamina = 100;
	Stamina = 45;
	Coins = 0;

	RunningSpeed = 650.f;
	SpringingSpeed = 1000.f;

	bSprintkeyDown = false;

	//Init enums
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;


}

void AMain::SetMovementStatus(EMovementStatus status)
{
	MovementStatus = status;
	if (MovementStatus == EMovementStatus::EMS_Sprinting) {
		GetCharacterMovement()->MaxWalkSpeed = SpringingSpeed;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AMain::SprintKeyDown()
{
	bSprintkeyDown = true;
}

void AMain::SprintKeyUp()
{
	bSprintkeyDown = false;
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::TurnUpRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMain::SprintKeyDown); //Shift
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMain::SprintKeyUp); //Disable shifts
}

void AMain::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f)) {

		//find which way is forward
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMain::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f)) {

		//find which way is forward
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AMain::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::TurnUpRate(float rate)
{
	AddControllerPitchInput(rate * BaseLoopUpRate * GetWorld()->GetDeltaSeconds());
}


void AMain::DecrementHealth(float amount)
{
	Health -= amount;
	if (Health <= 0.f) {
		Die();
	}
	
}

void AMain::IncrementCoins(int32 amount)
{
	Coins += amount;
}

void AMain::Die()
{

}
