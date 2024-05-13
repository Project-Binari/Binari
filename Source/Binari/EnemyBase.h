// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h" 
#include "EnemyBase.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle  UMETA(DisplayName = "Idle"),
	Attack UMETA(DisplayName = "Attack"),
	Follow UMETA(DisplayName = "Follow")
};

UCLASS()
class BINARI_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float DetectionRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		float AttackDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
		EEnemyState CurrentState;

	void Damage(float DamageAmount);

	void Stun(float StunDuration);

protected:
	virtual void BeginPlay() override;

	void SetState(EEnemyState NewState);

	void HandleIdle();
	void HandleAttacking();
	void HandleFollowing();

	FTimerHandle StunTimerHandle;

	bool isStunned;
	void EndStun();

	void Die();

public:	
	virtual void Tick(float DeltaTime) override;

private:
	ACharacter* PlayerCharacter;

	float AttackRange;
	float RecognitionRange;

	float DistanceToPlayer;

	void SetPlayerCharacter();

	void CalculateDistanceToPlayer();
};
