// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HumanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECTKK_API AHumanPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//TsubclassOf is reference to the UMG asset in the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =" Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	/** variable to hold the widget after creating it*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Widgets")
	UUserWidget* HUDOverlay;

protected:
	virtual void BeginPlay() override;
};
