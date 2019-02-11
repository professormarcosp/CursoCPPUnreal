// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALDEIMOS_API ABotAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	ABotAIController();
	
	//função responsável por dar o controle do Pawn(inimigo) 
	//ao Controller.Ou Seja BotCharacter será controlado pelo
	//ABotAiController quando for possuido(Possess) por este
	//Controlador
	virtual void Possess(APawn* InPawn) override;

	//O SensingComponent Encapsula configurações e funcionalidades sensoriais(visão, audição) de um ator.
	UPROPERTY(EditDefaultsOnly)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditDefaultsOnly)
	class UBlackboardComponent* BlackBoardComp;

	//Função Delegate que irá ser chamada
	//quando a função OnSeePawn ocorrer.
	UFUNCTION()
	void OnSeePawn(class APawn* SensedPawn);
	
	
};
