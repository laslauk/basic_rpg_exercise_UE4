// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayerController.h"
#include "Blueprint/UserWidget.h"

void AHumanPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BEGIN PLAY HUMANPLAYERCONTORL"));
	if (HUDOverlayAsset) {
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
		if (HUDOverlay) {
			UE_LOG(LogTemp, Warning, TEXT("LUOTIIN HUDOVERLAY"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO EI ONNISTUNUI"));
	}

	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible); //Hud is visible or not
	
	
}
