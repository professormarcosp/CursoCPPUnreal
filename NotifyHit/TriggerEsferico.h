// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "TriggerEsferico.generated.h"

/**
 * 
 */
UCLASS()
class COLISAOOVERLAP_API ATriggerEsferico : public ATriggerSphere
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ColisaoDetectada(AActor* me, AActor* other);
	//me -> eu mesmo  - other - quem colidiu comigo

	UFUNCTION()
	void DeixouDeColidir(AActor* me, AActor* other);
	//me -> eu mesmo  - other - quem deixou de colidir comigo
		
};
