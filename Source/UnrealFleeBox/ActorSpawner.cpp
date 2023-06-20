// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorSpawner.h"
#include "Components/BoxComponent.h"
#include "ActorToSpawn.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance_CPP.h"

// Sets default values
AActorSpawner::AActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}


/* Handle to manage the timer */
FTimerHandle TimerHandle;
float SpawInterval = 1.0f;

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
    
    // Get MyGameInstance and set level
    MyGameInstance = Cast<UMyGameInstance_CPP>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (MyGameInstance)
    {
        switch (MyGameInstance->Level) {
            case 0:
                SpawInterval = 0.3f;
                break;
            case 1:
                SpawInterval = 0.2f;
                break;
            case 2:
                SpawInterval = 0.1f;
                break;
        }
    }
    
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AActorSpawner::SpawnActor, SpawInterval, true, 0.0f);
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorSpawner::SpawnActor()
{
    int XLocation = FMath::RandRange(-2500, 1900);
    FVector SpawnLocation = FVector(XLocation, 0, 2500);
    FRotator SpawnRotation = GetActorRotation();

    GetWorld()->SpawnActor<AActorToSpawn>(SpawnLocation, SpawnRotation);
}
