// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PersonagemTPS.generated.h"

UCLASS()
class PERSONAGEM_API APersonagemTPS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagemTPS();

protected:
	
	UPROPERTY(EditAnywhere, Category = "Arma")
	TSubclassOf<class AArma> BP_ArmaTipoRifle;
	
	UPROPERTY(BlueprintReadOnly, Category = "Pulo")
	bool bEstaPulando;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoverParaFrente(float Valor);

	void MoverDireita(float Valor);

	//Crouch
	void Agachar();

	//UnCrouch
	void Levantar();

	void Pular();

	void PararPulo();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraPersonagem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
