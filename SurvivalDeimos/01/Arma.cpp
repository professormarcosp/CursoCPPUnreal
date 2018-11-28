// Fill out your copyright notice in the Description page of Project Settings.

#include "Arma.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AArma::AArma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MalhaDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Malha da Arma"));

}

// Called when the game starts or when spawned
void AArma::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

