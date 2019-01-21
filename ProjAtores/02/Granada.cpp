// Fill out your copyright notice in the Description page of Project Settings.

#include "Granada.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AGranada::AGranada()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ColisorDoAtor = CreateDefaultSubobject<USphereComponent>(FName("Colisor"));
	ColisorDoAtor->SetSphereRadius(12.f);
	ColisorDoAtor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = ColisorDoAtor;
	
	MalhaDoAtor = CreateDefaultSubobject<UStaticMeshComponent>(FName("Malha"));
	MalhaDoAtor->SetRelativeLocation(FVector(3.2f, 0.f, 0.f));
	MalhaDoAtor->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	MalhaDoAtor->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>Granada(TEXT("StaticMesh'/Game/FBX/granada.granada'"));

	if (Granada.Succeeded())
	{
		MalhaDoAtor->SetStaticMesh(Granada.Object);
	}


}

// Called when the game starts or when spawned
void AGranada::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGranada::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

