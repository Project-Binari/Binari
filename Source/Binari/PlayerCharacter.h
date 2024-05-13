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

	void SetPower(int8 NewPower);
	void SetSoulCount(int8 NewSoulCount);

	void Damage(float DamageAmount);

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Attack();
	void AttackLevel1(const TArray<AActor*>& NearbyEnemies);
	void AttackLevel2(const TArray<AActor*>& NearbyEnemies);
	void AttackLevel3(const TArray<AActor*>& NearbyEnemies);

	TArray<AActor*> GetNearbyEnemy();
	bool GetNearestEnemy(FVector& OutEnemyLocation, const TArray<AActor*>& NearbyEnemies);

	void UseSkill();

	void Dash();

	void StunEnemy();

	void Die();

	float HealthPoints;

	float ManaPoints;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private: 
	float AttackRange;
	float AttackDamage;

	uint8 Power;
	uint8 SoulCount;

	float DashDistance;
	float DashSpeed;
	bool isDashing;

	float StunRange;
	float StunDuration;
};
