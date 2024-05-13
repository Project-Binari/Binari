// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class BINARI_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyBase();

	void Stun(float StunDuration);

protected:
	virtual void BeginPlay() override;

	FTimerHandle StunTimerHandle;

	bool isStunned;

	void EndStun();

public:	
	virtual void Tick(float DeltaTime) override;

};
