// Fill out your copyright notice in the Description page of Project Settings.

#include "InserirGranadas.h"
#include "Granada.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"


// Sets default values
AInserirGranadas::AInserirGranadas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColisorDoAtor = CreateDefaultSubobject<USphereComponent>(FName("Colisor"));
	RootComponent = ColisorDoAtor;

}

// Called when the game starts or when spawned
void AInserirGranadas::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor<AGranada>(BpGranada, GetActorLocation(), GetActorRotation());
	
}

// Called every frame
void AInserirGranadas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

