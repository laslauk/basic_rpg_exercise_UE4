// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"
#include "Explosive.h"

AExplosive::AExplosive()
{
	damage = 15.f;
}

void AExplosive::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	UE_LOG(LogTemp, Warning, TEXT("Explosive:OnOverlapBEGIN"));


	//Check if overlap is player

	if (OtherActor) {
		AMain* Main = Cast<AMain>(OtherActor); //null jos ei onistu

		if (Main) {
			UE_LOG(LogTemp, Warning, TEXT("Vähennetään HP"));
			Main->DecrementHealth(damage);
		}
	}


}

void AExplosive::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{ 
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("Explosive::OnOverlapEnd"));
}
