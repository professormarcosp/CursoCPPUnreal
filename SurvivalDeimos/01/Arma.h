// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arma.generated.h"


UCLASS()
class PERSONAGEM_API AArma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arma")
	class USkeletalMeshComponent* MalhaDaArma;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
