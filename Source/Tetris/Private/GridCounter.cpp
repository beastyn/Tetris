// Fill out your copyright notice in the Description page of Project Settings.

#include "GridCounter.h"
#include "Math/UnrealMath.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGridCounter::UGridCounter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGridCounter::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Cols; j++)
		{
			CellsPositionCalc(i,j);
			
			if (GridData.Num() < Rows*Cols)
			{
				GridData.Add(FGridData(i, j, CellsPositionCalc(i, j), false));
			}
			
		}
	}
	
}


// Called every frame
void UGridCounter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

FVector2D UGridCounter::CellsPositionCalc(int32 i, int32 j) 
{
		
	TArray<TArray<FVector2D>> AllCellsPosition;
	ArrayInitialization(AllCellsPosition);
	
	for (int32 i = 0; i < Rows; i++)
	{
		for (int32 j = 0; j < Cols; j++)
		{
			if (&AllCellsPosition != nullptr) 
			{
				AllCellsPosition[i][j] = FVector2D((UnitLength / 2 * Cols - j * UnitLength), (UnitLength / 2 * Rows - i * UnitLength));
			}
		}
	}
	DrawLines(AllCellsPosition);
	return AllCellsPosition[i][j];
}

TArray<FGridData> UGridCounter::GetGridData()
{
	return GridData;
}

FVector2D UGridCounter::GetGridMaxXY()
{
	return FVector2D(UnitLength / 2 * Cols, UnitLength / 2 * Rows);
}

FVector2D UGridCounter::GetGridMinXY()
{
	return FVector2D(-UnitLength / 2 * Cols + UnitLength, -UnitLength / 2 * Rows + UnitLength);
}

float UGridCounter::GetUnitLength()
{
	return UnitLength;
}

void UGridCounter::ArrayInitialization(TArray<TArray<FVector2D>> &AllCellsPosition)
{
	for (int32 i = 0; i < Rows; i++)
	{		
			TArray<FVector2D> ForInitArray;
			ForInitArray.Init(FVector2D(0, 0), Cols);
			AllCellsPosition.Add(ForInitArray);
	}
}

void UGridCounter::DrawLines(TArray<TArray<FVector2D>> &AllCellsPosition)
{
	for (int32 i = 0; i < Rows; i++)
	{
		DrawDebugLine(
			GetWorld(),
			FVector(AllCellsPosition[i][0] + UnitLength / 2, 141),
			FVector(AllCellsPosition[i][Cols - 1].X - UnitLength / 2, AllCellsPosition[i][Cols - 1].Y + UnitLength / 2, 141),
			FColor(255, 0, 0),
			false, 1000, 0,
			5.333
		);
	}
	for (int32 j = 0; j < Cols; j++)
	{
		DrawDebugLine(
			GetWorld(),
			FVector(AllCellsPosition[0][j] + UnitLength / 2, 141),
			FVector(AllCellsPosition[Rows - 1][j].X + UnitLength / 2, AllCellsPosition[Rows - 1][j].Y - UnitLength / 2, 141),
			FColor(255, 0, 0),
			false, 1000, 0,
			5.333
		);
	}
	
	
	DrawDebugLine(
		GetWorld(),
		FVector(AllCellsPosition[Rows - 1][0].X + UnitLength / 2, AllCellsPosition[Rows-1][0].Y - UnitLength / 2, 141),
		FVector(AllCellsPosition[Rows - 1][Cols - 1].X - UnitLength / 2, AllCellsPosition[Rows - 1][Cols - 1].Y - UnitLength / 2, 141),
		FColor(255, 0, 0),
		false, 1000, 0,
		5.333
	);
	
	DrawDebugLine(
		GetWorld(),
		FVector(AllCellsPosition[0][Cols - 1].X - UnitLength / 2, AllCellsPosition[0][Cols - 1].Y + UnitLength / 2, 141),
		FVector(AllCellsPosition[Rows - 1][Cols - 1].X - UnitLength / 2, AllCellsPosition[Rows - 1][Cols - 1].Y - UnitLength / 2, 141),
		FColor(255, 0, 0),
		false, 1000, 0,
		5.333
	);
	
}
