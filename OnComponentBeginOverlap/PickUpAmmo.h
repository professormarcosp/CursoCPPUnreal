// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpAmmo.generated.h"

UCLASS()
class COLISAOOVERLAP_API APickUpAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "PickUpAmmo")
	class UBoxComponent* Colisor;

	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
	class UStaticMeshComponent* ObjetoDoPickup;

	UPROPERTY(EditAnywhere, Category = "PickUpAmmo")
	class UAudioComponent* SomDoPickup;

	UFUNCTION()
		void ColidiuComPickup(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	
};
