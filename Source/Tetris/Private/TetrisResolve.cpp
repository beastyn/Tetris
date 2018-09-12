// Fill out your copyright notice in the Description page of Project Settings.

#include "TetrisResolve.h"
#include "GridCounter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTetrisResolve::UTetrisResolve()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTetrisResolve::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTetrisResolve::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTetrisResolve::CheckSolving(TArray<FGridData> &GridData, UStaticMeshComponent* EmptyCellMesh)
{
	for (int32 j = 0; j < 20; j++)
	{
		for (int32 i = 0; i < 10; i++)
		{
			if (GridData[j * 10 + i].isFilled)
			{
				FilledCellNum++;
			}
		}
		if (FilledCellNum == 10)
		{
			MaxSolvedRow = j;
			bSolved = true;
			SolvedRowsNum++;
			for (int32 x = 0; x < 10; x++)
			{
				GridData[j * 10 + x].CubeFromBrick->DestroyComponent();
				GridData[j * 10 + x].CubeFromBrick = EmptyCellMesh;
				GridData[j * 10 + x].isFilled = false;
			}
			
		}
		FilledCellNum = 0;
	}
	

}
void UTetrisResolve::CorrectBrickPositions(TArray<FGridData> &GridData, UStaticMeshComponent* EmptyCellMesh)
{
	if (bSolved)
	{
		for (int32 x = MaxSolvedRow - 1; x >= 0; x--)
		{
			for (int32 y = 0; y < 10; y++)
			{
				
					if (GridData[x * 10 + y].isFilled)
					{
						GridData[x * 10 + y].CubeFromBrick->AddRelativeLocation(FVector(0, SolvedRowsNum*(-100), 0));
						GridData[x * 10 + y + SolvedRowsNum*10].CubeFromBrick = GridData[x * 10 + y].CubeFromBrick;
						GridData[x * 10 + y].CubeFromBrick = EmptyCellMesh;
						GridData[x * 10 + y].isFilled = false;
						GridData[x * 10 + SolvedRowsNum*10 + y].isFilled = true;
					}
			}
		}

		MaxSolvedRow = 0;
		SolvedRowsNum = 0;

	}
	
}