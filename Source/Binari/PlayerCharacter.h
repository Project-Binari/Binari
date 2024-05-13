// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BINARI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	void SetPower(int32 NewPower);

	void SetSoulCount(int32 NewSoulCount);

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void UseSkill();

	void Attack();

	void AttackLevel1(const TArray<AActor*>& NearbyEnemies);

	void AttackLevel2(const TArray<AActor*>& NearbyEnemies);

	void AttackLevel3(const TArray<AActor*>& NearbyEnemies);

	TArray<AActor*> GetNearbyEnemy();

	bool GetNearestEnemy(FVector& OutEnemyLocation, const TArray<AActor*>& NearbyEnemies);

	void Dash();

	void StunEnemy();

	void Die();

	float HealthPoints;

	float ManaPoints;

	bool IsDead() const;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float AttackRange;
	float AttackDamage;

	int32 Power;
	int32 SoulCount;

	float DashDistance;
	float DashSpeed;
	bool isDashing;

	float StunRange;
	float StunDuration;
};
