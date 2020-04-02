// Fill out your copyright notice in the Description page of Project Settings.

#pragma once 
//pragma once prevents including same file twice

#include "CoreMinimal.h" 
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h" //boilerplate code of garbage collection and reflections

/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECTKK_API UMyObject : public UObject
{
	GENERATED_BODY()


public:

	UPROPERTY(BluePrintReadWrite, Category = "MyVariables") //read write bp
	float MyFloat;

	UFUNCTION(BluePrintCallable, Category = "MyFunctions")
	void MyVoidFunc();

	UMyObject();
	
};
