#pragma once

#include "GridData.generated.h"

USTRUCT()
struct FGridData {

	GENERATED_BODY()

	UPROPERTY()
	int32 IndexI;
	int32 IndexJ;
	FVector2D CellPosition;
	UStaticMeshComponent* CubeFromBrick;
	bool isFilled;
	
public:
	FGridData() {};

	FGridData(int32 IndI, int32 IndJ, FVector2D CellPos, UStaticMeshComponent* Cube, bool isFil)
		: IndexI(IndI), IndexJ(IndJ), CellPosition(CellPos), CubeFromBrick(Cube), isFilled(isFil)
	{ }
	
};