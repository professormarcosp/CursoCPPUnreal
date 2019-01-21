// Fill out your copyright notice in the Description page of Project Settings.

#include "MeuGameMode.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Granada.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void AMeuGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> LocalGranadas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), LocalGranadas);
	UE_LOG(LogTemp, Warning, TEXT("Numero de TargetPoints Encontrados %d"), LocalGranadas.Num());

	FActorSpawnParameters params = FActorSpawnParameters();

	for (auto It : LocalGranadas)
	{
		GetWorld()->SpawnActor<AGranada>(It->GetActorLocation(), It->GetActorRotation(), params);
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("Ator Gerado"));
		UE_LOG(LogTemp, Warning, TEXT("Transform = %s"), *It->GetActorLocation().ToString());
	}

}




