// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GridData.h"
#include "BrickPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBrickStop);

class ABrick;
class UGridCounter;
class UTetrisResolve;
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

	// from grid
	
	UGridCounter* Grid;
	
	UPROPERTY(BlueprintReadOnly, Category = "Grid Data")
		float UnitLength;

	UPROPERTY(BlueprintReadOnly, Category = "Grid Data")
		FVector2D GridMaxXY;

	UPROPERTY(BlueprintReadOnly, Category = "Grid Data")
		FVector2D GridMinXY;

	
	UPROPERTY()
	TArray<FGridData> GridData;
	
	UPROPERTY()
	TArray<FGridData> UpdatedGridData;

	UPROPERTY()
	UStaticMeshComponent* EmptyCellMesh;

	//from Brick
	UPROPERTY(BlueprintReadOnly, Category = "Brick Data")
	TArray<UStaticMeshComponent*> CubesMeshesForBrick;


	//for input in BP
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool IsAbleMoveDown = true;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool IsAbleMoveLeft = true;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool IsAbleMoveRight = true;

private:


	FTimerHandle TimerHandle;
	
	//from Brick
	UPROPERTY()
	ABrick* Brick;

	UPROPERTY()
	UClass* BrickSome;

	UTetrisResolve* TetrisResolve;
	
	UPROPERTY()
	TArray<int32> CubeIndex = { 0,0 };

	bool isSolved = false;


public:


	ABrickPlayerController();
	virtual void Tick(float DeltaTime) override;

	// info about grid

	void GetOnceGridData();

	//Info from Brick for movement in BP
	
	UFUNCTION(BlueprintCallable, Category = "Brick Data")
	int32 GetBrickType();

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
		TArray<FVector> GetCubesCoordinates();

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
		TArray<int32>GetCubeIndex(FVector CubeCoordinate);

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
		float GetMinYCoordinate(TArray<FVector> CubesRelativeLocation);

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
		float GetMaxXCoordinate(TArray<FVector> CubesRelativeLocation);

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
		float GetMinXCoordinate(TArray<FVector> CubesRelativeLocation);

	
	// moving brick and cube meshes

	UFUNCTION()
	void TestTimer();

	UFUNCTION()
	void InstantMoveDown();

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	void CheckForDownSide(TArray<FVector> CubesCoordinates);
	
	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	void CheckForLeftSide(TArray<FVector> CubesCoordinates);

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	void CheckForRightSide(TArray<FVector> CubesCoordinates);

	void SpawnNewBrick();

	//Grid update
	void SetEmptyStaticMeshesinGrid();

	void SetGridFilledCell(TArray<FVector> CubesCoordinates, TArray<UStaticMeshComponent*> CubesMeshesForBrick);

	//for Brick Stop Event

	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnBrickStop OnBrickStop;

	
	


	

};
