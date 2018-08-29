// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Brick.generated.h"


class UGridCounter;
class ABrickConstructor;

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



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FVector2D GetGridMaxXY();
	FVector2D GetGridMinXY();
	float GetUnitLength();

	TArray<UStaticMeshComponent*> GetStaticMeshesforCubes();
	
	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	TArray<FVector> GetCubesCoordinates();

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	float GetMinYCoordinate(TArray<FVector> CubesRelativeLocation);

	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	float GetMaxXCoordinate(TArray<FVector> CubesRelativeLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Cube Positions")
	float GetMinXCoordinate(TArray<FVector> CubesRelativeLocation);


	
		

private:


	TArray<UStaticMeshComponent*> CubesForFigure ;

	UGridCounter* Grid = nullptr;
		
	
};
