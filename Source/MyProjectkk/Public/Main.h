// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

//scoped enum with class
UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName ="ExhaustedRecovering"),
	ESS_MAX UMETA(DisplayName = "DefaultMAX")
}

UCLASS()
class MYPROJECTKK_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category  = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	/** Set movement status and running speed */
	void SetMovementStatus(EMovementStatus status);

	FORCEINLINE void SetStaminaStatus(EStaminaStatus status) { StaminaStatus = status; }

	/** Camera boom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta =(AllowPrivateAcces = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera for player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAcces = "true"))
	class UCameraComponent* FollowCamera;

	// Turn with keys rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLoopUpRate;

	/** Press down enable sprint*/
	void SprintKeyDown();
	/** Released to stop sprinting */
	void SprintKeyUp();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);

	/** called v ia input to turn at ag iven rate
	* @param Rate this is normalized rate 1.e 1.0 means 100% desired turn rate
	*/
	void TurnAtRate(float rate);

	/** called via input to look up/down at a given rate
	* @param Rate this is normalized rate 1.e 1.0 means 100% desired turn rate
	*/
	void TurnUpRate(float rate);

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera;  }



	/**
		PLAYER STATS 
	*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SpringingSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,  Category = "Player stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player stats")
	float MaxStamina;

	bool bSprintkeyDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	int32 Coins;

	void DecrementHealth(float amount);

	void IncrementCoins(int32 amount);

	void Die();
};
