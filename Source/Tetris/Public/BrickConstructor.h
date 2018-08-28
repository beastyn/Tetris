// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrickConstructor.generated.h"

UCLASS()
class TETRIS_API ABrickConstructor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrickConstructor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//TArray<FVector> GenerateFirstFigure();

	TArray<UStaticMeshComponent*> CubesForFigure;

	UPROPERTY()
		TArray<FVector> CubesRelativeLocation = { FVector(0,0,0), FVector(0,0,0), FVector(0,0,0), FVector(0,0,0) };

	UPROPERTY(EditDefaultsOnly)
		UStaticMesh* MeshForCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Brick")
		AActor* Test;

	//TArray<FVector> GetCubesCoordinates();
	
private:


};
