// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

UMyObject::UMyObject() {
	MyFloat = 0;
}

void UMyObject::MyVoidFunc() {
	UE_LOG(LogTemp, Warning, TEXT("Our warning text!")); //LogTemp on category, warning on että keltainen
}