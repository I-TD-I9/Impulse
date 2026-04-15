// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

UENUM(BlueprintType)
enum class ERoundPhase : uint8
{
	WaitingToStart,
	InRound,
	BetweenRounds,
	GameOver
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundEnded);

UCLASS()
class IMPULSE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable) FOnRoundStarted OnRoundStarted;
	UPROPERTY(BlueprintAssignable) FOnRoundEnded OnRoundEnded;

	UPROPERTY(BlueprintReadOnly) ERoundPhase CurrentPhase = ERoundPhase::WaitingToStart;
	UPROPERTY(BlueprintReadOnly) int32 EnemiesAlive = 0;

	UFUNCTION(BlueprintCallable) void StartRound();
	UFUNCTION(BlueprintCallable) void OnEnemyDied();
	UFUNCTION(BlueprintCallable) void EndGame();
};