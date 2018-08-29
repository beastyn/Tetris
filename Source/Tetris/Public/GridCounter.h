// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridCounter.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TETRIS_API UGridCounter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridCounter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FVector2D CellsPositionCalc(int32 i, int32 j) ;

	FVector2D GetGridMaxXY();

	FVector2D GetGridMinXY();

	float GetUnitLength();

	void ArrayInitialization(TArray<TArray<FVector2D>> &AllCellsPosition);

	void DrawLines(TArray<TArray<FVector2D>> &AllCellsPosition);

private:
	int32 UnitLength = 100;
	int32 Rows = 20;
	int32 Cols = 10;
	
};
