// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MeuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJATORES_API AMeuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void StartPlay() override;

	
	
};
