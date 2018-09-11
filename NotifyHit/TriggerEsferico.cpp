// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerEsferico.h"
#include "Engine/Engine.h"

void ATriggerEsferico::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ATriggerEsferico::ColisaoDetectada);
	//Função OnActorBeginOverlap é Delegate
	//Assim ele permite que outras funções possam ser anexadas a ela
	//Logo quando o evento de overlap ocorrer a função OnActorBeginOverlap vai ser disparada
	//e todas as outras funções que tiverem sido anexadas a ela via delegate também serão chamadas
	//assim estamos indicando que a função ColisaoDetectada seja chamada quando a funcao
	//OnActorBeginOverlap for chamada.
	//Isso é realizado passando o endereço da função com &
	//this indica que queremo que este objeto Trigger seja considerado ao anexar função
	//Logo é neste(this) objeto que caso o evento overlap ocorra ele vai chamar a função 
	//OnActorBeginOverlap que consequentemente vai chamar a função ColisaoDetectada
	// Pois você programou isso! via Delegate! :)
	OnActorEndOverlap.AddDynamic(this, &ATriggerEsferico::DeixouDeColidir);
	//Anexando uma função à função OnActorEndOverlap para que ela seja acionada quando esta função ocorrer.
}

void ATriggerEsferico::ColisaoDetectada(AActor* me, AActor* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, 
		FString::Printf(TEXT("Entrou no Trigger Em Overlap em: %s"), *GetActorLocation().ToString()));
	//other->Destroy();
	//Quando o player ou algum elemento tocar o Trriger será destruido e uma mensagem aparecerá na tela
}

void ATriggerEsferico::DeixouDeColidir(AActor * me, AActor * other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Deixou de Sobrepor(Overlap) O trigger em: %s"), *GetActorLocation().ToString()));

}





