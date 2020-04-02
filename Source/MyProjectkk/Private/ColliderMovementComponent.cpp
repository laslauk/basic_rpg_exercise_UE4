// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); //kutsutaan parentin impl

	//Check to make sure is valid and allowed move

	//1. check is owner
	//2. if updated component is valid
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	//Get and clear vector from collider


	//consume input vector käyttää Addinputvecotrin vectorin ja asettaa sen nollaksi
	float movementSpeed = 450.f;
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * movementSpeed;

		FHitResult hit;
	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, hit); //this causes movement
	}

	//if we bvump into something,. slide along the side of it

	if (hit.IsValidBlockingHit()) {
		SlideAlongSurface(DesiredMovementThisFrame, 1.0f - hit.Time, hit.Normal, hit);
	}
}