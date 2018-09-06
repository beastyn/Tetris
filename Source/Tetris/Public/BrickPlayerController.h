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
	TArray<int32> CubeIndex = { 0,0 };

	UPROPERTY()
	TArray<FGridData> UpdatedGridData;
	
	UStaticMeshComponent* EmptyCellMesh;

	bool isSolved = false;


public:
	ABrickPlayerController();
	virtual void Tick(float DeltaTime) override;

	// info about grid

	void GetOnceGridData();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Data")
	float UnitLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Data")
	FVector2D GridMaxXY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Data")
	FVector2D GridMinXY;
	
	// info about brick
	
	UFUNCTION(BlueprintCallable, Category = "Brick Data")
	ABrick* GetBrick();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Brick Data")
	TArray<UStaticMeshComponent*> CubesMeshesForBrick;
	
	//Info for movement

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsAbleMoveDown = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsAbleMoveLeft = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool IsAbleMoveRight = true;

	// moving brick
	
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



	
	


	

};
