// Fill out your copyright notice in the Description page of Project Settings.


#include "AtorControlado.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"



// Sets default values
AAtorControlado::AAtorControlado()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malha Estatica"));
	StaticMesh->SetSimulatePhysics(true);
	RootComponent = StaticMesh;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Minha Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->AddRelativeLocation(FVector(-330, 0, 130));



}

// Called when the game starts or when spawned
void AAtorControlado::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAtorControlado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAtorControlado::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &AAtorControlado::MoveVerticalmente);
	PlayerInputComponent->BindAxis("MouseX", this, &AAtorControlado::RotacionaEmZ);




}

void AAtorControlado::MoveVerticalmente(float eixoVertical)
{
	FVector PosicaoAtual = GetActorLocation();
	FVector Frente = GetActorForwardVector();
	SetActorLocation(PosicaoAtual + (Frente * eixoVertical * Velocidade));


}

void AAtorControlado::RotacionaEmZ(float eixoHorizontal)
{
	FRotator RotacaoAtual = GetActorRotation();
	FRotator eixoZ = FRotator::MakeFromEuler(FVector(0.f, 0.f, 1.f));
	SetActorRotation(RotacaoAtual + (eixoZ * eixoHorizontal * VelocidadeDeRotacao));
}

