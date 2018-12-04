// Fill out your copyright notice in the Description page of Project Settings.

#include "Arma.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Public/DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
AArma::AArma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MalhaDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MalhaDaArma"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshDaArma(TEXT("SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));
	if (MeshDaArma.Succeeded())
	{
		MalhaDaArma->SetSkeletalMesh(MeshDaArma.Object);
	}
	RootComponent = MalhaDaArma;

	SetaDaArma = CreateDefaultSubobject<UArrowComponent>(FName("SetaCanodaArma"));
	SetaDaArma->SetupAttachment(Cast<USceneComponent>(MalhaDaArma), FName("MuzzleFlashSocket"));
	/*SetaDaArma->AttachToComponent(MalhaDaArma, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("MuzzleFlashSocket"));*/
	SetaDaArma->SetRelativeLocation(FVector(1.5f, 0.f, -1.2f));
	SetaDaArma->SetRelativeScale3D(FVector(0.3f, 0.8f, 0.7f));
	
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

void AArma::Atirar()
{
	UArrowComponent* SetaDaArma = FindComponentByClass<UArrowComponent>();
	if (SetaDaArma)
	{
		FVector Inicio = SetaDaArma->GetComponentLocation();
		FVector Direcao = SetaDaArma->GetComponentRotation().Vector();
		FVector Fim = Inicio + (Direcao * 1000);
		FHitResult InfoImpacto;
		FCollisionQueryParams Parametros;
		Parametros.AddIgnoredActor(this);
		Parametros.AddIgnoredActor(GetOwner());
		Parametros.bTraceComplex = true;
		bool AcertouEmAlgo = GetWorld()->LineTraceSingleByChannel(InfoImpacto, Inicio, Fim, ECollisionChannel::ECC_Visibility, Parametros);
		if (AcertouEmAlgo)
		{
			//Cause Dano a depender de quem acertou
			UE_LOG(LogTemp, Warning, TEXT("Acertou em Algo"));
		}

		DrawDebugLine(GetWorld(), Inicio, Fim, FColor::Red, false, 5.0f, (uint8)0, 1.0f);
	}
}

