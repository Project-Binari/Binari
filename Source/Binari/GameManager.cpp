// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "MyPlayerController.h"
#include "PlayerCharacter.h"

AGameManager::AGameManager() 
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
}
