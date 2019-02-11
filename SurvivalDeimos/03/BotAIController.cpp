// Fill out your copyright notice in the Description page of Project Settings.

#include "BotAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "BotCharacter.h"
#include "Engine/Engine.h"
#include "Arma.h"




ABotAIController::ABotAIController()
{
	//Construtor que criar o component de sensores do BotInimigo
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnSensingComp"));
	//Aqui Configuramos como os sensores do inimigo deverão atuar
	//Deve fazer a varredura sensorial a cada 1/4 de segundo .25
	PawnSensingComp->SensingInterval = .25f;
	//Deve detectar ser sensível a detectação apenas de Player(Jogadores)
	PawnSensingComp->bOnlySensePlayers = true;
	//O angulo de visão de detecção deve ser 180 graus, isso facilita ver
	//também de costas
	PawnSensingComp->SetPeripheralVisionAngle(180.f);
	//O raio de visão será de 3000 unidades
	PawnSensingComp->SightRadius = 3000.f;

	//Aqui criamos um component de BT para manipular a BT criada
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorTreeComp"));
	//Da mesma forma foi criado um component de BlackBoard para podermos
	//Colocar variáveis, alterar seu valor, etc no BlackBoard Criado
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackBoardComp"));


}

void ABotAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	//Se o sensor do inimigo disparar o evento OnSeePawn significa que ele detectou o nosso jogador(que para ele é seu inimigo)
	//Neste caso iremos anexar, amarrar, fazer um binding da função para uma função
	//criada por nós para esta classe
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ABotAIController::OnSeePawn);

	if (BehaviorTree)
	{
		//Aqui iniciamos o BlackBosard e a BehaivouTree
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
		//Aqui Setamos que o valor da variável booleana DevePerambular deve ser true
		//Ou seja se ele ainda não viu o jogador ele deve ficar patrulhando
		BlackBoardComp->SetValueAsBool("DevePerambular", true);
	}
}

void ABotAIController::OnSeePawn(APawn* SensedPawn)
{
	if (BlackBoardComp && SensedPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Eu estou te Vendo"));
		
		//aqui setamos a variável do BlackBoard Inimigo com o valor do objeto
		//SensedPawn: Este objeto é o retornado quando o game está em execução
		//e o sensor do inimigo detecta seu inimigo(no caso o player)
		//Então o objeto player e colocado em Inimigo que é Object no BlackBoard
		BlackBoardComp->SetValueAsObject("Inimigo", SensedPawn);
		//Se esta função for chamada significa que o inimigo VIU(see) um jogador (Pawn) e neste caso deve parar de Perambular
		//Assim colocamos false no blackboard para que a arvore de comportamento leia
		//e Trate este valor.
		BlackBoardComp->SetValueAsBool("DevePerambular", false);
		//Estamos na classe Controller do Bot(inimigo)
		//Precisamos obter uma referência ao objeto Inimigo(BotCharacter)
		//Que está sendo possuido por este Controller(BotAiController)
		//GetPawn() Devolve esta referência mas devolve via uma classe genérica do tipo APawn. como Acharacter é filha de APawn e BotCharacter é filho de Acharacter podemos especilizar este retorno
		//USamos Cast para tranformar o objeto genérico retornado do tipo APawn em ABotCharcter.
		ABotCharacter* Bot = Cast<ABotCharacter>(GetPawn());
		//Depois chamados o método atirar da arma deste BotInimigo
		//Logo toda vez que estiver vendo o nosso player ele vai atirar
		//com sensbilidade de 0.25 do sensor
		Bot->ArmaInimigo->Atirar();
	}
}
