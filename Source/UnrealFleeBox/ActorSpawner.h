// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameInstance_CPP.h"
#include "ActorSpawner.generated.h"


UCLASS()
class UNREALFLEEBOX_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    
    
public:

    UFUNCTION()
    void SpawnActor();

protected:
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    class UBoxComponent* SpawnVolume;
    
    class UMyGameInstance_CPP* MyGameInstance;
};
