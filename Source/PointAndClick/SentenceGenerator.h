// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <map>
#include <cassert>
#include "Components/SceneComponent.h"
#include "SentenceGenerator.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POINTANDCLICK_API USentenceGenerator : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USentenceGenerator();

	UFUNCTION(BlueprintCallable, Category = "SentenceGenerator")
		void ReadSentenceFile(FString fileNmae);

	UFUNCTION(BlueprintCallable, Category = "SentenceGenerator")
		FString GenerateSentence();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	TMap<FString, TArray<FString>> markovSets;
	TArray<FString> startingSets;
};
