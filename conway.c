#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conway.h"

struct World* gol_alloc_world(uint32 width, uint32 height) {
    struct World* world = (struct World*) malloc(sizeof(struct World));
    
    if (!world) {
        fprintf(stderr, "Failed to allocate memory for game of life\n");
        return NULL;
    }
    
    world->width = width;
    world->height = height;
    world->size = width * height;
    world->cells = (uint8*) calloc(width * height, sizeof(uint8));
    
    if (!world->cells) {
        fprintf(stderr, "Failed to allocate memory for cells\n");
        free(world);
        return NULL;
    }
    
    return world;
}

void gol_free_world(struct World* world) {
    if (world) {
        if (world->cells) {
            free(world->cells);
        }
        free(world);
    }
}

void gol_set_cell(struct World* world, uint32 x, uint32 y, enum CellState state) {
    uint8* cell_ptr = world->cells + (y * world->width) + x;
    int x_offset_left, x_offset_right, y_offset_top, y_offset_bottom;

    if (x == 0) {
        x_offset_left = world->width - 1;
    } else {
        x_offset_left = - 1;
    }

    if (x == (world->width - 1)) {
        x_offset_right = -(world->width - 1);
    } else {
        x_offset_right = 1;
    }

    if (y == 0) {
        y_offset_top = world->size - world->width;
    } else {
        y_offset_top = - world->width;
    }

    if (y == (world->height - 1)) {
        y_offset_bottom = -(world->size - world->width);
    } else {
        y_offset_bottom = world->width;
    }
    
    if (state == ALIVE) {
        // Set the cell to alive by setting the first bit to 1
        *(cell_ptr) |= 0x01;

        // Increment the surrounding cells alive neighbour counts by adding 1 to the second bit
        *(cell_ptr + y_offset_top + x_offset_left) += 0x02;
        *(cell_ptr + y_offset_top) += 0x02;
        *(cell_ptr + y_offset_top + x_offset_right) += 0x02;
        *(cell_ptr + x_offset_left) += 0x02;
        *(cell_ptr + x_offset_right) += 0x02;
        *(cell_ptr + y_offset_bottom + x_offset_left) += 0x02;
        *(cell_ptr + y_offset_bottom) += 0x02;
        *(cell_ptr + y_offset_bottom + x_offset_right) += 0x02;
    } else {
        *(cell_ptr) &= ~0x01;

        // Decrement the surrounding cells alive neighbour counts by subtracting 1 from the second bit
        *(cell_ptr + y_offset_top + x_offset_left) -= 0x02;
        *(cell_ptr + y_offset_top) -= 0x02;
        *(cell_ptr + y_offset_top + x_offset_right) -= 0x02;
        *(cell_ptr + x_offset_left) -= 0x02;
        *(cell_ptr + x_offset_right) -= 0x02;
        *(cell_ptr + y_offset_bottom + x_offset_left) -= 0x02;
        *(cell_ptr + y_offset_bottom) -= 0x02;
        *(cell_ptr + y_offset_bottom + x_offset_right) -= 0x02;
    }
}

enum CellState gol_get_cell_state(struct World* world, uint32 x, uint32 y) {
    uint8* cell_ptr = world->cells + (y * world->width) + x;
    return (*cell_ptr & 0x01) != 0 ? ALIVE : DEAD;
}

void gol_run_step(struct World* game) {
    uint8* new_cells = (uint8*) calloc(game->width * game->height, sizeof(uint8));
    
    if (!new_cells) {
        fprintf(stderr, "Failed to allocate memory for new cells\n");
        return;
    }
    
    memcpy(new_cells, game->cells, game->size);

    uint8* cell_ptr = new_cells;

    uint32 x, y, neighbour_count;

    for (y = 0; y < game->height; y++) {
        for (x = 0; x < game->width; x++) {
            cell_ptr = new_cells + (y * game->width) + x;

            if (*cell_ptr == 0) {
                continue;
            }

            neighbour_count = *cell_ptr >> 1;

            if (*cell_ptr & 0x01) {
                if ((neighbour_count != 2) && (neighbour_count != 3)) {
                    gol_set_cell(game, x, y, DEAD);
                }
            } else {
                if (neighbour_count == 3) {
                    gol_set_cell(game, x, y, ALIVE);
                }
            }
        }
    }
}