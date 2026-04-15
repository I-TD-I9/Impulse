// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

void AMyGameModeBase::StartRound()
{
	CurrentPhase = ERoundPhase::InRound;
	OnRoundStarted.Broadcast();
}

void AMyGameModeBase::OnEnemyDied()
{
	EnemiesAlive--;
	if (EnemiesAlive <= 0)
	{
		CurrentPhase = ERoundPhase::BetweenRounds;
		OnRoundEnded.Broadcast();
	}
}

void AMyGameModeBase::EndGame()
{
	CurrentPhase = ERoundPhase::GameOver;
}