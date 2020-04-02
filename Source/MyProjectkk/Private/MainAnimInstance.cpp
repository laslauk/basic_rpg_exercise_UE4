// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Main.h"

void UMainAnimInstance::NativeInitializeAnimation() {
	if (Pawn == nullptr) {
		Pawn = TryGetPawnOwner();

		if (Pawn) {
			Main = Cast<AMain>(Pawn);
	
		}
	}
}

void UMainAnimInstance::UpdateAnimationProperties() {
	if (Pawn == nullptr) {
		Pawn = TryGetPawnOwner();
	}

	if (Pawn) {
		FVector speed = Pawn->GetVelocity();
		FVector lateralSpeed = FVector(speed.X, speed.Y, 0.f);
		MovementSpeed = lateralSpeed.Size(); //vektorin amgnitunde == vauhti

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		if (Main == nullptr) {
			Main = Cast<AMain>(Pawn);
		}

	}
}