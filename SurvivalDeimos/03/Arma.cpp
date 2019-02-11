// Fill out your copyright notice in the Description page of Project Settings.

#include "Arma.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Public/DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/World.h"
#include "Animation/SkeletalMeshActor.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"



// Sets default values
AArma::AArma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EfeitoMuzzle = nullptr;
	ImpactoSangue = nullptr;
	ImpactoGeral = nullptr;
	DecalImpactoGeral = nullptr;
	SomDoTiro = nullptr;

	MalhaDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MalhaDaArma"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshDaArma(TEXT("SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));

	if (MeshDaArma.Succeeded())
	{
		MalhaDaArma->SetSkeletalMesh(MeshDaArma.Object);
	}

	RootComponent = MalhaDaArma;
	
	//Abaixo criamos um componente SETA (Arrow Component) dentro do construtor da classe
	SetaDaArma = CreateDefaultSubobject<UArrowComponent>(FName("SetaCanodaArma"));
	
	//Aqui solicitamos que este construtor seja anexado, atrelado, aclopado a malhada da arma
	//Contudo é solicitado um attach para algo que ainda não foi configurado pois primeiro a classe c++ é executada e depois qualquer blueprint que tem esta classe como pai
	//Assim o mesh ou skeletalmesh da arma ainda não estará disponível aqui pois está sendo setado na bleprint.
	//Logo precisamos configurar no código a malhadadaarma!
	//Outra coisa importante e recomendada pela unreal engine é que no construtor
	//use a função SEtupAttachment para fazer o attach de algum componente a seu dono
	//logo somente usar attachtocomponent fora do construtor
	SetaDaArma->SetupAttachment(MalhaDaArma, FName("MuzzleFlashSocket"));
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

		if (SomDoTiro)
		{
			UGameplayStatics::PlaySoundAtLocation(SetaDaArma, SomDoTiro, Inicio);
		}


		if (AcertouEmAlgo)
		{
			//Cause Dano a depender de quem acertou
			UE_LOG(LogTemp, Warning, TEXT("Acertou em Algo"));
			//Qual o ator que o raio impactou
			AActor* Ator = InfoImpacto.GetActor();
			//Se a classe do ator que o raio atingiu for do tipo SkeletalMeshActor ou subclasses dela entre neste if. ImpactoSangue precisa ser válido
			if (Ator->GetClass()->IsChildOf(ASkeletalMeshActor::StaticClass()) && ImpactoSangue)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactoSangue, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), true);
			}
			//Se não for um inimigo humanoide não queremos que seja sangue
			else if (ImpactoGeral)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactoGeral, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), true);

				FVector TamanhoVariavel = FVector(FMath::RandRange(10.f, 50.f));
				UGameplayStatics::SpawnDecalAttached(DecalImpactoGeral, TamanhoVariavel, InfoImpacto.GetComponent(), NAME_None, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 60.f);
			}

		}

		//DrawDebugLine(GetWorld(), Inicio, Fim, FColor::Red, false, 5.0f, (uint8)0, 1.0f);

		//Se For setado algum efeito Muzzle na BP da Arma EfeitoMuzzle receberá um endereço de memória
		//Endereço de memória é diferente de zero e logo if(EfeitoMuzzle) retornará verdadeiro, pois em C e C++ 0(zero)  é falso e QUALQUER COISA Diferente de Zero é TRUE (Verdadeiro)
		//Assim EfeitoMuzzle == nullptr está testando se EfeitoMuzzle = zerpo ou falso
		if (EfeitoMuzzle)
		{
			//Para Componentes usamos estas funções GetComponent, já para atores seriam GetActorLocation, etc
			FVector Localizacao = SetaDaArma->GetComponentLocation();
			FRotator Rotacao = SetaDaArma->GetComponentRotation();
			//Se valores forem iguais podemos iniciar os valores de X< Y e Z  de um  vetor usando este construtor que recebe um parâmetro
			//O mesmo que FVector(0.9f, 0.9f, 0.9f)
			FVector Escala = FVector(0.9f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EfeitoMuzzle, Localizacao, Rotacao, Escala, true);
		}
	}
}

