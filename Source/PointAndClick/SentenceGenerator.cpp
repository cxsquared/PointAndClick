// Fill out your copyright notice in the Description page of Project Settings.

#include "PointAndClick.h"
#include "SentenceGenerator.h"


// Sets default values for this component's properties
USentenceGenerator::USentenceGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USentenceGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void USentenceGenerator::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void USentenceGenerator::ReadSentenceFile(FString fileName)
{
	if (fileName.IsEmpty())
	{
		return;
	}

	markovSets.Empty();

	FString FullPath = FPaths::GameDir() + "Content/Data/" + fileName + ".txt";
	FString fileString;
	FFileHelper::LoadFileToString(fileString, *FullPath);
	TArray<FString> words;

	fileString.ParseIntoArray(words, _T(" "), true);

	int index;
	bool startingSet = true;

	for (index = 0; index < words.Num()-2; index++)
	{	
		if (startingSet){
			startingSets.Push(words[index] + " " + words[index + 1]);
			startingSet = false;
		}
		if (words[index+1].Contains(".")){
			startingSet = true;
			index++;
		}
		else {
			markovSets[words[index] + " " + words[index + 1]].Push(words[index + 3]);
		}
	}

}

FString USentenceGenerator::GenerateSentence()
{
	if (markovSets.Num() <= 0) {
		return "";
	}

	FString result;

	result += startingSets[FMath::RandRange(0,startingSets.Num() - 1)];

	while (!result.Contains("."))
	{
		TArray<FString> set;
		result.ParseIntoArray(set, _T(" "), true);
		TArray<FString> nextWords;
		nextWords = markovSets[set[set.Num() - 2] + " " + set[set.Num() - 1]];
		result += nextWords[FMath::RandRange(0, nextWords.Num() - 1)];
	}

	return result;
}

