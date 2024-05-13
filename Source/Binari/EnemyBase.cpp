// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

    isStunned = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::Stun(float StunDuration)
{
    if (!isStunned)
    {
        isStunned = true;

        SetActorEnableCollision(false);

        GetWorldTimerManager().SetTimer(StunTimerHandle, this, &AEnemyBase::EndStun, StunDuration, false);
    }
}

void AEnemyBase::EndStun()
{
    isStunned = false;

    SetActorEnableCollision(true);
}
