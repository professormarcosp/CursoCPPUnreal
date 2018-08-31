// Fill out your copyright notice in the Description page of Project Settings.

#include "PickUpAmmo.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
APickUpAmmo::APickUpAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Colisor = CreateDefaultSubobject<UBoxComponent>(FName("Colisor"));
	Colisor->InitBoxExtent(FVector(16.f, 32.f, 16.f));
	Colisor->SetCollisionProfileName("Trigger");
	RootComponent = Colisor;

	ObjetoDoPickup = CreateDefaultSubobject<UStaticMeshComponent>(FName("ObjetoDoPickup"));
	ObjetoDoPickup->SetRelativeLocation(FVector(0.f, 0.f, -16.f));
	ObjetoDoPickup->SetupAttachment(RootComponent);

	SomDoPickup = CreateDefaultSubobject<UAudioComponent>(FName("SomDoPickup"));
	SomDoPickup->bAutoActivate = false;
	SomDoPickup->SetupAttachment(RootComponent);

	Colisor->OnComponentBeginOverlap.AddDynamic(this, &APickUpAmmo::ColidiuComPickup);
	   
}

// Called when the game starts or when spawned
void APickUpAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*DrawDebugBox(GetWorld(), GetActorLocation(), FVector(16.f, 32.f, 16.f), FColor::Red, true, -1, 0, 0.15f);*/

}

void APickUpAmmo::ColidiuComPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{ 
		UE_LOG(LogTemp, Error, TEXT("OverlappedComponent = %s "), *OverlappedComp->GetName());
		//OverlappedComponent é o componente deste ator(PickupAmmo) que sofreu overlap!
		//Neste caso OverlappedComponent = Colisor 
		UE_LOG(LogTemp, Warning, TEXT("OtherActor = %s "), *OtherActor->GetName());
		//OtherActor é o ator se sobrepoem a este ator
		//Ou seja um ator foi em direcao a este pickup e neste caso temos nesta variável
		//o nome dele: OtherActor = DefaultPawn_0 
		UE_LOG(LogTemp, Error, TEXT("OtherComp = %s "), *OtherComp->GetName());
		//OtherComp é o componente do outro ator e que fez overlap com este ator(PickupAmmo)
		//OtherComp = CollisionComponent0
		UE_LOG(LogTemp, Warning, TEXT("OtherBodyIndex = %d "), OtherBodyIndex);
		//OtherBodyIndex: O índice do componente que está sendo sobreposto
				

		//Ativa o som, pois ele foi desativado
		SomDoPickup->Activate(true);
		//Indica que o som não irá parar caso o proprietário(owner) deste componente de som
		//seja destruído
		SomDoPickup->bStopWhenOwnerDestroyed = false;
		SomDoPickup->Play(0.0f);
		Destroy();
	 }

}

