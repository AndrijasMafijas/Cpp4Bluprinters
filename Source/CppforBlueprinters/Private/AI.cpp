// Fill out your copyright notice in the Description page of Project Settings.


#include "AI.h"

// Sets default values
AAI::AAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AAI::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

void AAI::GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const
{
	Location = GetMesh()->GetSocketLocation(EyeSocketName);
	Rotation = GetMesh()->GetSocketRotation(EyeSocketName);
}

void AAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void AAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AAI::CanSeePlayer() const
{
    if (!PlayerPawn) return false;

    FVector AIToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
    float Distance = AIToPlayer.Size();

    if (Distance > SightRadius)
        return false;

    AIToPlayer.Normalize();

    FVector Forward = GetActorForwardVector();
    float Dot = FVector::DotProduct(Forward, AIToPlayer);
    float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(Dot));

    if (AngleDegrees > SightAngle)
        return false;

    // Možeš dodati linijski trag da proveriš da li je igrač vidljiv (npr. bez prepreka)
    FHitResult HitResult;
    FVector Start = GetActorLocation() + FVector(0, 0, 50); // malo iznad zemlje
    FVector End = PlayerPawn->GetActorLocation();

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

    if (bHit && HitResult.Actor.IsValid() && HitResult.Actor.Get() == PlayerPawn)
    {
        // Igrač je vidljiv
        return true;
    }

    return false;
}
/*
void AAI::ChasePlayer(float DeltaTime)
{
    if (!PlayerPawn) return;

    FVector Direction = PlayerPawn->GetActorLocation() - GetActorLocation();
    Direction.Z = 0.f;
    Direction.Normalize();

    AddMovementInput(Direction, 1.0f);

    // Okreni AI da gleda ka igraču
    FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
    SetActorRotation(FRotator(0.f, LookAtRotation.Yaw, 0.f));
}*/


