// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Brick.generated.h"


class UGridCounter;
class UTestGrid;
struct FGridData;

UCLASS()
class TETRIS_API ABrick : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:

	
	UPROPERTY()
	TArray<UStaticMeshComponent*> CubesForFigure;

	UPROPERTY()
	TArray<int32> CubeIndex = { 0,0 };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Brick Data
	TArray<UStaticMeshComponent*> GetStaticMeshesforCubes();
	
	TArray<FVector> GetCubesCoordinates();

	float GetMinYCoordinate(TArray<FVector> CubesRelativeLocation);

	float GetMaxXCoordinate(TArray<FVector> CubesRelativeLocation);
		
	float GetMinXCoordinate(TArray<FVector> CubesRelativeLocation);

	TArray<int32> GetCubeIndex(FVector CubeCoordinate);

	UFUNCTION()
	void DeleteEmptyBrick();
		

	

	
		

	
};
