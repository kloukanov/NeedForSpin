#include "CaveGenerator.h"
#include "DrawDebugHelpers.h"
#include "Components/InputComponent.h"
#include "Components/InstancedStaticMeshComponent.h"


ACaveGenerator::ACaveGenerator() {
	PrimaryActorTick.bCanEverTick = false;

	WallMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallMesh"));
    RootComponent = WallMesh;
}


void ACaveGenerator::BeginPlay() {
	Super::BeginPlay();

	// TODO: remove this is TEMP ---------
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
        EnableInput(PlayerController);

        if (InputComponent) {
            InputComponent->BindAction("GenerateCave", IE_Pressed, this, &ACaveGenerator::GenerateCave);
        }
    }
	// --------------------------------
	
}

void ACaveGenerator::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ACaveGenerator::GenerateCave() {
    InitRandomGrid(Width, Height);

    for(int i = 0; i < Iterations; i++){
        CellularAutomata();
    }

    VisualizeCave();
}

void ACaveGenerator::InitRandomGrid(int _Width, int _Height) {
    CaveGrid.SetNum(_Height);
    for(int y = 0; y < _Height; y++) {
        CaveGrid[y].SetNum(_Width);
        for(int x = 0; x < _Width; x++) {
            CaveGrid[y][x] = (FMath::RandRange(0.0f, 1.0f) < StartingFillPercentage) ? 0 : 1;
        }
    }
}

void ACaveGenerator::CellularAutomata() {

    TArray<TArray<int>> TempGrid = CaveGrid;

    for (int y = 0; y < CaveGrid.Num(); y++) {
        for (int x = 0; x < CaveGrid[y].Num(); x++) {
            
            int NeighborWalls = CountWallNeighbors(x, y);

            if (CaveGrid[y][x] == 1) {
                // Floor
                TempGrid[y][x] = (NeighborWalls >= 5) ? 0 : 1;
            }
            else {
                // Wall
                TempGrid[y][x] = (NeighborWalls >= 4) ? 0 : 1;
            }
        }
    }
    
    CaveGrid = TempGrid;
}

int ACaveGenerator::CountWallNeighbors(int X, int Y)
{
    int WallCount = 0;

    for (int OffsetY = -1; OffsetY <= 1; OffsetY++) {
        for (int OffsetX = -1; OffsetX <= 1; OffsetX++) {

            if (OffsetX == 0 && OffsetY == 0) {
                continue;
            }

            int NeighborX = X + OffsetX;
            int NeighborY = Y + OffsetY;

            if (NeighborX >= 0 && NeighborX < CaveGrid[0].Num() && NeighborY >= 0 && NeighborY < CaveGrid.Num()) {
                if (CaveGrid[NeighborY][NeighborX] == 0) {
                    WallCount++;
                }
            }
            else {
                WallCount++;
            }
        }
    }

    return WallCount;
}

void ACaveGenerator::VisualizeCave() {

	// FlushPersistentDebugLines(GetWorld());
	WallMesh->ClearInstances();
	

    FVector TileHalfSize = FVector(TileSize * 0.5f, TileSize * 0.5f, 500.f);

    for(int y = 0; y < CaveGrid.Num(); y++) {
        for(int x = 0; x < CaveGrid[y].Num(); x++) {
            FVector Location = FVector(x * TileSize, y * TileSize, FMath::RandRange(-200.f, 200.f));
            if(CaveGrid[y][x] == 0){
                // we have a wall
                // DrawDebugBox(GetWorld(), Location, TileHalfSize, FColor::Green, true, -1.f, 0, 5.0f);
				FTransform InstanceTransform(FRotator(0, FMath::RandRange(0.0f, 90.0f), 0), Location, FVector(1.3f));
                WallMesh->AddInstance(InstanceTransform);
            }
        }
    }

	WallMesh->SetWorldLocation(FVector(0, 0, -0.5f));
}