#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MyAIController.generated.h"

UCLASS()
class CPPFORBLUEPRINTERS_API AMyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AMyAIController();

protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UAISenseConfig_Sight* SightConfig;

    UFUNCTION()
        void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);
};
