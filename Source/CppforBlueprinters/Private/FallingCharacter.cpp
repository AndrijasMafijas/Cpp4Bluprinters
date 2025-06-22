#include "FallingCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"


AFallingCharacter::AFallingCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Kreiraj i postavi SpringArm (CameraBoom)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.f;
    CameraBoom->bUsePawnControlRotation = true;
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;
}

void AFallingCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AFallingCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetActorLocation().Z < -150.f)
    {
        USkeletalMeshComponent* MeshComponent = GetMesh();
        if (MeshComponent && !MeshComponent->IsSimulatingPhysics())
        {
            MeshComponent->SetSimulatePhysics(true);
        }
    }
}

void AFallingCharacter::TurnAtRate(float Rate)
{
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFallingCharacter::LookUpAtRate(float Rate)
{
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFallingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AFallingCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AFallingCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &AFallingCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUpRate", this, &AFallingCharacter::LookUpAtRate);
}

void AFallingCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AFallingCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}
