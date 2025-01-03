#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CaveGenerator.generated.h"

UCLASS()
class NEEDFORSPIN_API ACaveGenerator : public AActor
{
	GENERATED_BODY()
	
private:

	TArray<TArray<int>> CaveGrid;

	void InitRandomGrid(int Width, int Height);

	void CellularAutomata();

	int CountWallNeighbors(int X, int Y);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	float StartingFillPercentage = 0.46f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int TileSize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int Width;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int Height;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
	int Iterations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (AllowPrivateAccess = "true"))
    class UInstancedStaticMeshComponent* WallMesh;

public:	
	ACaveGenerator();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void GenerateCave();

	TArray<TArray<int>> GetCaveGrid() const { return CaveGrid; }

	void VisualizeCave();

};
