#include <raylib.h>
#include <stdio.h>
#include "conway.h"

uint32 CELL_SIZE = 2;

int main(int argc, char* argv[]) {
    // Initialize the window
    const int screenWidth = 400;
    const int screenHeight = 400;

    SetTraceLogLevel(LOG_ERROR);
    
    InitWindow(screenWidth, screenHeight, "Conway's Game of Life");

    SetTargetFPS(60);

    struct World* world = gol_alloc_world(200, 200);

    if (argc > 1) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
            return 1;
        }

        FILE* file = fopen(argv[1], "r");

        if (file) {
            uint32 x, y;
            while (fscanf(file, "%u %u", &x, &y) == 2) {
                gol_set_cell(world, x, y, ALIVE);
            }
            fclose(file);
        } else {
            fprintf(stderr, "Failed to open file: %s\n", argv[1]);
        }
    } else {
        // Initialize a glider
        gol_set_cell(world, 1, 0, ALIVE);
        gol_set_cell(world, 2, 1, ALIVE);
        gol_set_cell(world, 0, 2, ALIVE);
        gol_set_cell(world, 1, 2, ALIVE);
        gol_set_cell(world, 2, 2, ALIVE);
    }

    bool firstIteration = true;
    int generation = 0;
    
    while (!WindowShouldClose()) {
        if (firstIteration) {
            firstIteration = false;
        } else {
            gol_run_step(world);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (uint32 y = 0; y < world->height; y++) {
            for (uint32 x = 0; x < world->width; x++) {
                enum CellState state = gol_get_cell_state(world, x, y);
                if (state == ALIVE) {
                    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
                } else {
                    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
                }
            }
        }

        DrawText(TextFormat("Generation: %d", generation), 120, 380, 20, DARKGRAY);

        EndDrawing();

        generation++;
    }

    CloseWindow();

    gol_free_world(world);

    return 0;
}