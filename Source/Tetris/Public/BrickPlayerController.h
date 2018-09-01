// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GridData.h"
#include "BrickPlayerController.generated.h"

class ABrick;
struct FGridData;
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
		
	UPROPERTY()
	ABrick* Brick;

	UPROPERTY()
	UClass* BrickSome;

	UPROPERTY()
	TArray<FGridData> UpdatedGridData;

	UPROPERTY()
	TArray<int32> CubeIndex = { 0,0 };

	bool IsAbleMoveDown = true;


public:
	ABrickPlayerController();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void InstantMoveDown();

	void GetOnceGridData();

	void SpawnNewBrick();

	void SetGridFilledCell(TArray<FVector> &CubesCoordinates);

	void CheckForDownSide(TArray<FVector> &CubesCoordinates);
	
	UFUNCTION(BlueprintCallable, Category = "Grid Data")
	float GetUnitLength();

	UFUNCTION(BlueprintCallable, Category = "Grid Data")
	FVector2D GetGridMaxXY();

	UFUNCTION(BlueprintCallable, Category = "Grid Data")
	FVector2D GetGridMinXY();

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	TArray<FVector> GetCubesCoordinates();

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	float GetMinYCoordinate(TArray<FVector> CubesRelativeLocation);

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	float GetMaxXCoordinate(TArray<FVector> CubesRelativeLocation);

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	float GetMinXCoordinate(TArray<FVector> CubesRelativeLocation);


	

};
