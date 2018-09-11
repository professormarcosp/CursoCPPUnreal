// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RayCastPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRACERAYCASTING_API ARayCastPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	FVector LocalizacaoPontoDeVisaoDoPlayer;

	UPROPERTY()
	FRotator RotacaoPontoDeVisaoDoPlayer;


public:
	virtual void SetupInputComponent() override;

	void AtirarRayCast();

	virtual void Tick(float Deltatime) override;


	
};
