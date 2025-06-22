#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

AMyAIController::AMyAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 1500.0f;
    SightConfig->LoseSightRadius = 1600.0f;
    SightConfig->PeripheralVisionAngleDegrees = 90.0f;
    SightConfig->SetMaxAge(5.0f);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    AIPerceptionComponent->ConfigureSense(*SightConfig);
    AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIPerceptionComponent)
    {
        AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetPerceived);
    }
}

void AMyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // (Opciono: ovde možeš dodati nešto ako želiš, ali samo ovako zadovoljava linker)
}

void AMyAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
    if (Stimulus.WasSuccessfullySensed())
    {
        // Vidi igrača → kreni ka njemu
        MoveToActor(Actor, 5.f); // 5.f = koliko blizu da priđe
        UE_LOG(LogTemp, Warning, TEXT("AI vidi igrača i kreće ka njemu!"));
    }
    else
    {
        // Izgubio ga iz vida → stani
        StopMovement();
        UE_LOG(LogTemp, Warning, TEXT("AI izgubio igrača iz vida!"));
    }
}
