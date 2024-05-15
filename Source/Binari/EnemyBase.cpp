
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

    AttackRange = 10;
    isStunned = false;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

    SetPlayerCharacter();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CalculateDistanceToPlayer();

    switch (CurrentState)
    {
        case EEnemyState::Idle:
            HandleIdle();
            break;

        case EEnemyState::Attack:
            HandleAttacking();
            break;

        case EEnemyState::Follow:
            HandleFollowing();
         break;

        default:
            break;
    }
}

void AEnemyBase::SetPlayerCharacter()
{
    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
}

void AEnemyBase::CalculateDistanceToPlayer()
{
    if (PlayerCharacter)
    {
        DistanceToPlayer = FVector::Dist(GetActorLocation(), PlayerCharacter->GetActorLocation());

        if (DistanceToPlayer > RecognitionRange)
            SetState(EEnemyState::Idle);
        else if (DistanceToPlayer <= AttackRange)
            SetState(EEnemyState::Attack);
        else
            SetState(EEnemyState::Follow);
    }
}

void AEnemyBase::SetState(EEnemyState NewState)
{
    CurrentState = NewState;
}


void AEnemyBase::HandleIdle()
{
  
}

void AEnemyBase::HandleAttacking()
{
  
}

void AEnemyBase::HandleFollowing()
{
   
}

void AEnemyBase::Damage(float DamageAmount)
{
    Health -= DamageAmount;

    if (Health <= 0) 
    {
        Die();
    }
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

void AEnemyBase::Die()
{
    // TODO
}
