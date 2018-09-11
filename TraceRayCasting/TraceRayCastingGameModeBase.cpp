// Fill out your copyright notice in the Description page of Project Settings.

#include "TraceRayCastingGameModeBase.h"
#include "RayCastPlayerController.h"

//Indica qual será a classe padrão do PlayerController neste GameMode
ATraceRayCastingGameModeBase::ATraceRayCastingGameModeBase()
{
	PlayerControllerClass = ARayCastPlayerController::StaticClass();
}

