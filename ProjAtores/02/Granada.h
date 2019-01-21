// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Granada.generated.h"

UCLASS()
class PROJATORES_API AGranada : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGranada();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Granada")
	class UStaticMeshComponent* MalhaDoAtor;

	class USphereComponent* ColisorDoAtor;
	
};
