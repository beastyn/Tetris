#pragma once

#include "GridData.generated.h"

USTRUCT()
struct FGridData {

	GENERATED_BODY()

	UPROPERTY()
	int32 IndexI;
	int32 IndexJ;
	FVector2D CellPosition;
	bool isFilled;
	
public:
	FGridData() {};

	FGridData(int32 IndI, int32 IndJ, FVector2D CellPos, bool isFil)
		: IndexI(IndI), IndexJ(IndJ), CellPosition(CellPos), isFilled(isFil)
	{ }
	
};