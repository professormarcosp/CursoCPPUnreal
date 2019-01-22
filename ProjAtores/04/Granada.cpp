// Fill out your copyright notice in the Description page of Project Settings.

#include "Granada.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"


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

	SomDaExplosao = CreateDefaultSubobject<UAudioComponent>(FName("Som Da Explosao"));
	SomDaExplosao->bAutoActivate = false;
	SomDaExplosao->bAutoDestroy = true;
	SomDaExplosao->SetupAttachment(MalhaDoAtor);

	Explosao = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticulaExplosao"));
	Explosao->bAutoActivate = false;
	Explosao->bAutoDestroy = true;
	Explosao->SetupAttachment(MalhaDoAtor);

	ConstructorHelpers::FObjectFinder<UStaticMesh>Granada(TEXT("StaticMesh'/Game/FBX/granada.granada'"));

	ConstructorHelpers::FObjectFinder<USoundCue>SomGranada(TEXT("SoundCue'/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue'"));

	ConstructorHelpers::FObjectFinder<UParticleSystem>ParticulaExplosao(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	if (Granada.Succeeded() && SomGranada.Succeeded() && ParticulaExplosao.Succeeded())
	{
		MalhaDoAtor->SetStaticMesh(Granada.Object);
		SomDaExplosao->SetSound(SomGranada.Object);
		Explosao->SetTemplate(ParticulaExplosao.Object);
	}


}

// Called when the game starts or when spawned
void AGranada::BeginPlay()
{
	Super::BeginPlay();
	MalhaDoAtor->SetSimulatePhysics(true);
	MalhaDoAtor->SetEnableGravity(true);
	GetWorldTimerManager().SetTimer(Temporizador, this, &AGranada::ExplodirGranada, 5.f, false);
	
}

void AGranada::ExplodirGranada()
{
	SetLifeSpan(5.5f);
	SomDaExplosao->Play();
	Explosao->ActivateSystem();
	MalhaDoAtor->SetVisibility(false);
}

// Called every frame
void AGranada::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

