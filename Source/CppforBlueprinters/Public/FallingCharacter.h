#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FallingCharacter.generated.h"

UCLASS()
class CPPFORBLUEPRINTERS_API AFallingCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AFallingCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        class UCameraComponent* FollowCamera;

public:
    virtual void Tick(float DeltaTime) override;

    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);

    // Osetljivost za okretanje (možeš menjati u editoru)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
        float BaseTurnRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
        float BaseLookUpRate;
};
