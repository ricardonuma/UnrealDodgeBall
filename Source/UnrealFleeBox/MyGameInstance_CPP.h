// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance_CPP.generated.h"

/**
 * 
 */
UCLASS()
class UNREALFLEEBOX_API UMyGameInstance_CPP : public UGameInstance
{
	GENERATED_BODY()
	
    void Init() override;
    
public:
    
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    int32 Seconds;
    
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    int32 Minutes;
    
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    int32 Level;
};
