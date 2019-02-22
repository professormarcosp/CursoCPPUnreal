// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeSurvivalDeimos.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALDEIMOS_API AGameModeSurvivalDeimos : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Health")
	TSubclassOf<class UUserWidget> PLayerHUDClass;

	UPROPERTY()
	class UUserWidget* WidgetAtual;

	
	
};
