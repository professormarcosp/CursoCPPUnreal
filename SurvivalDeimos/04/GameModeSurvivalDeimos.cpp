// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeSurvivalDeimos.h"
#include "PersonagemTPS.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AGameModeSurvivalDeimos::BeginPlay()
{
	Super::BeginPlay();
	//Aqui obtenho o personagem do jogo e coloco em Player
	APersonagemTPS* Player = Cast<APersonagemTPS>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Aqui se for setada algo como classe do HUD entramos
	if (PLayerHUDClass != nullptr)
	{
		//WidgetAtual passa a ser A widget criada (a tela com o health)
		WidgetAtual = CreateWidget<UUserWidget>(GetWorld(), PLayerHUDClass);
		//se for criada com sucesso a função add to view port é chamada e
		//a widget é colocada na tela com a barra de health do jogador
		if (WidgetAtual)
		{
			WidgetAtual->AddToViewport();
		}
	}
}
