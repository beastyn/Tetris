// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BrickPlayerController.generated.h"

class ABrick;
/**
 * 
 */
UCLASS()
class TETRIS_API ABrickPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	FTimerHandle TimerHandle;
	ABrick* Brick;
	UClass* BrickSome;

	bool isBottom = false;



public:
	ABrickPlayerController();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void InstantMoveDown();
	
};
