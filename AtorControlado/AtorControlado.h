// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AtorControlado.generated.h"

UCLASS()
class ATORCOMINPUTSTECLADO_API AAtorControlado : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAtorControlado();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametros Gerais")
	float Velocidade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametros Gerais")
	float VelocidadeDeRotacao;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametros Gerais")
	float Altura;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parametros Gerais")
	bool IsAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dados Adicionais")
	FName Nome;

	UPROPERTY(VisibleDefaultsOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly)
	class UCameraComponent* Camera;
	   	  
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveVerticalmente(float eixoVertical);

	UFUNCTION()
	void RotacionaEmZ(float eixoHorizontal);


};
