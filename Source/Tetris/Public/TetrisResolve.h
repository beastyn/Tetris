// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TetrisResolve.generated.h"

struct FGridData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TETRIS_API UTetrisResolve : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTetrisResolve();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CheckSolving(TArray<FGridData> &GridData, UStaticMeshComponent* EmptyCellMesh);
	void CorrectBrickPositions(TArray<FGridData> &GridData, UStaticMeshComponent* EmptyCellMesh, int32 j);

private:

	int32 FilledCellNum = 0;
	int32 MaxSolvedRow = 0;
	int32 SolvedRowsNum = 0;
	UPROPERTY()
	//TArray<FGridData> GridData;
	bool bSolved = false;
};
