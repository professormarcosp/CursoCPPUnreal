// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Caixa.generated.h"

UCLASS()
class COLISAOOVERLAP_API ACaixa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACaixa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Caixa)
	class UBoxComponent* Colisor;

	UPROPERTY(EditAnywhere, Category = Caixa)
	class UStaticMeshComponent* MalhaDaCaixa;

	UPROPERTY(EditAnywhere, Category = Caixa)
	class UAudioComponent* SomDoHit;

	UPROPERTY(EditAnywhere, Category = Caixa)
	class UParticleSystemComponent* ParticulaHit;

	bool bDeuHit;

	//função que será anexada à função OnComponentHit
	UFUNCTION()
		void OcorreuHitNoComponente(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	
	
};
