// Fill out your copyright notice in the Description page of Project Settings.

#include "Caixa.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ACaixa::ACaixa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bDeuHit = false;

	Colisor = CreateDefaultSubobject<UBoxComponent>(FName("Colisor"));
	Colisor->SetSimulatePhysics(true);
	//O Mesmo que ativar Simulates Generate Hit Events
	Colisor->SetNotifyRigidBodyCollision(true);
	Colisor->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	RootComponent = Colisor;

	//Anexando a função OnComponentHit
	Colisor->OnComponentHit.AddDynamic(this, &ACaixa::OcorreuHitNoComponente);

	MalhaDaCaixa = CreateDefaultSubobject<UStaticMeshComponent>(FName("Malha"));
	MalhaDaCaixa->SetupAttachment(RootComponent);

	SomDoHit = CreateDefaultSubobject<UAudioComponent>(FName("SomDoHit"));
	SomDoHit->bAutoActivate = false;
	SomDoHit->bStopWhenOwnerDestroyed = false;
	SomDoHit->SetupAttachment(RootComponent);

	ParticulaHit = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particula"));
	ParticulaHit->bAutoActivate = false;
	ParticulaHit->SetupAttachment(RootComponent);
		   	  
	
}

// Called when the game starts or when spawned
void ACaixa::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACaixa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACaixa::OcorreuHitNoComponente(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherActor->ActorHasTag(FName("Caixa")))
	{ 
		//A primeira vez bDeuHit é falso
		//Logo !falso = true
		//Entra no if
		if (!bDeuHit) {
			SomDoHit->Activate(true);
			SomDoHit->Play(0.0f);
			ParticulaHit->Activate(true);
			//OtherActor->Destroy();
			//aqui sera true e com isso apenas um hit será acionado a programação acima
			bDeuHit = true;
		}

	}

}

