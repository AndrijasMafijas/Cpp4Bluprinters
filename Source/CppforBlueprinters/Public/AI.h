// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#include "AI.generated.h"   // mora biti POSLEDNJI include u header fajlu

UCLASS()
class CPPFORBLUEPRINTERS_API AAI : public ACharacter
{
	GENERATED_BODY()

private:
    // Cilj koji AI prati (igrač)
    APawn* PlayerPawn;

    // Koliko daleko AI može da vidi igrača (radius)
    UPROPERTY(EditAnywhere, Category = "AI")
        float SightRadius = 1500.f;

    // Koliko ugao gledanja (field of view) u stepenima
    UPROPERTY(EditAnywhere, Category = "AI")
        float SightAngle = 60.f;

    // Brzina AI-ja dok juri
    UPROPERTY(EditAnywhere, Category = "AI")
        float MoveSpeed = 400.f;

    // Da li je igrač trenutno u vidokrugu
    bool bCanSeePlayer = false;

    // Pomoćna funkcija za proveru da li AI vidi igrača
    bool CanSeePlayer() const;

    // Pomoćna funkcija da AI krene da ide ka igraču
    void ChasePlayer(float DeltaTime);

public:
	// Sets default values for this character's properties
	AAI();

	void GetActorEyesViewPoint(FVector& Location, FRotator& Rotation) const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName EyeSocketName;
};
