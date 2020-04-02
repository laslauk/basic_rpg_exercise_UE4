// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h" //THIS HAS TO BE LAST!!!!!!!! ERROR OTHERWISE generated.h

UCLASS()
class MYPROJECTKK_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent; };
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* mesh) { MeshComponent = mesh; }

	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent; };
	FORCEINLINE void SetSphereComponent(USphereComponent* sphere) { SphereComponent = sphere; }

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;
	FORCEINLINE UCameraComponent* GetUCameraComponent() { return Camera; };
	FORCEINLINE void SetCameraComponent(UCameraComponent* cam ) { Camera = cam; }

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* SpringArm;
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() { return SpringArm; };
	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* spring) { SpringArm = spring; }

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UColliderMovementComponent* OurColliderMovmenetComponent;

	//override

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);

	FVector2D CameraInput; //store mosue X Y
};
