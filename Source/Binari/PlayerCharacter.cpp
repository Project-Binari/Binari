
#include "PlayerCharacter.h"

#include "EnemyBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    HealthPoints = 100;
    ManaPoints = 50;

    Power = 0;
    SoulCount = 0;

    DashDistance = 1000.0f;
    DashSpeed = 2000.0f;
    isDashing = false;

    StunRange = 500.0f;
    StunDuration = 2.0f;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (isDashing)
    {
        FVector DashDirection = GetActorForwardVector();
        FVector NewLocation = GetActorLocation() + DashDirection * DashSpeed * DeltaTime;
        SetActorLocation(NewLocation);

        if (FVector::Dist(GetActorLocation(), GetActorLocation() + DashDirection * DashDistance) >= DashDistance)
        {
            isDashing = false;
        }
    }
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("UseSkill", IE_Pressed, this, &APlayerCharacter::UseSkill);

    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
    PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);

    PlayerInputComponent->BindAction("Stun", IE_Pressed, this, &APlayerCharacter::StunEnemy);
}

#pragma region Setter
void APlayerCharacter::SetPower(int8 NewPower)
{
    Power += NewPower;
}

void APlayerCharacter::SetSoulCount(int8 NewSoulCount)
{
    SoulCount += NewSoulCount;
}
#pragma endregion

#pragma region Move
void APlayerCharacter::MoveForward(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(Direction, Value);
    }
}

void APlayerCharacter::MoveRight(float Value)
{
    if (Controller != nullptr && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(Direction, Value);
    }
}
#pragma endregion

#pragma region Attack
void APlayerCharacter::Attack()
{
    FVector EnemyLocation;

    TArray<AActor*> NearbyEnemies = GetNearbyEnemy();

    if (Power >= 50 && SoulCount >= 30)
    {
        AttackLevel3(NearbyEnemies);
    }
    else if (Power >= 30 && SoulCount >= 15)
    {
        AttackLevel2(NearbyEnemies);
    }
    else if (Power >= 10)
    {
        AttackLevel1(NearbyEnemies);
    }
}

void APlayerCharacter::AttackLevel1(const TArray<AActor*>& NearbyEnemies)
{
    FVector NearestEnemyLocation;
    if (GetNearestEnemy(NearestEnemyLocation, NearbyEnemies))
    {
        // Attack nearest enemy
        // TODO: Implement attack logic here
    }
}

void APlayerCharacter::AttackLevel2(const TArray<AActor*>& NearbyEnemies)
{
    float AttackAngle = 90.0f; // TODO

    FVector PlayerForward = GetActorForwardVector();

    for (AActor* Enemy : NearbyEnemies)
    {
        FVector DirectionToEnemy = Enemy->GetActorLocation() - GetActorLocation();
        DirectionToEnemy.Normalize();

        float AngleToEnemy = FMath::RadiansToDegrees(FMath::Acos(DirectionToEnemy | PlayerForward));

        if (AngleToEnemy <= AttackAngle * 0.5f)
        {
            // Attack the enemy
            // TODO: Implement attack logic here
        }
    }
}

void APlayerCharacter::AttackLevel3(const TArray<AActor*>& NearbyEnemies)
{
    for (AActor* Enemy : NearbyEnemies)
    {
        // Attack the enemy
        // TODO: Implement attack logic here
    }
}
#pragma endregion

#pragma region Get Enemy
TArray<AActor*> APlayerCharacter::GetNearbyEnemy()
{
    TArray<AActor*> NearbyEnemies;
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        float Distance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
        if (Distance <= AttackRange)
        {
            NearbyEnemies.Add(Actor);
        }
    }

    return NearbyEnemies;
}

bool APlayerCharacter::GetNearestEnemy(FVector& OutEnemyLocation, const TArray<AActor*>& NearbyEnemies)
{
    if (NearbyEnemies.Num() <= 0) return false;

    float NearestDistance = TNumericLimits<float>::Max();
    AActor* NearestEnemy = nullptr;

    for (AActor* Actor : NearbyEnemies)
    {
        float Distance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
        if (Distance < NearestDistance)
        {
            NearestDistance = Distance;
            NearestEnemy = Actor;
        }
    }

    if (NearestEnemy != nullptr)
    {
        OutEnemyLocation = NearestEnemy->GetActorLocation();
        return true;
    }

    return false;
}
#pragma endregion

void APlayerCharacter::UseSkill() //TODO
{
    if (ManaPoints >= 0)
    {
        ManaPoints -= 0;
    }
}

void APlayerCharacter::Dash()
{
    if (!isDashing)
    {
        isDashing = true;
    }
}

void APlayerCharacter::StunEnemy()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyBase::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        if (FVector::Dist(Actor->GetActorLocation(), GetActorLocation()) <= StunRange)
        {
            AEnemyBase* Enemy = Cast<AEnemyBase>(Actor);
            if (Enemy)
            {
                Enemy->Stun(StunDuration);
            }
        }
    }
}

void APlayerCharacter::Damage(float DamageAmount)
{
    HealthPoints -= DamageAmount;

    if (HealthPoints <= 0)
    {
        Die();
    }
}

void APlayerCharacter::Die()
{
    // TODO
}
