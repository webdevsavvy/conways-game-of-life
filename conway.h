#ifndef CONWAY_H
#define CONWAY_H

#define uint32 unsigned int
#define uint8 unsigned char

/**
 * @brief Represents the state of the Game of Life.
 * @struct World
 */
struct World {
    uint32 width;
    uint32 height;
    uint32 size; // size of the world in bytes
    uint8* cells; // 1D array to store the state of each cell
};

enum CellState {
    DEAD = 0,
    ALIVE = 1
};

/**
 * @brief Load a world with a given width and height, and populate it with dead cells.
 * 
 * @param width The width of the world.
 * @param height The height of the world.
 * @return `struct World*` A pointer to the allocated world. 
 */
struct World* gol_alloc_world(uint32 width, uint32 height);

/**
 * @brief Unload a world and free its memory.
 * 
 * @param world The world to free.
 */
void gol_free_world(struct World* world);

/**
 * @brief Set the state of a cell in the world.
 * 
 * @param world The world to set the cell in.
 * @param x The x coordinate of the cell.
 * @param y The y coordinate of the cell.
 * @param state The state to set the cell to (ALIVE or DEAD).
 */
void gol_set_cell(struct World* world, uint32 x, uint32 y, enum CellState state);

/**
 * @brief Get the state of a cell in the world.
 * 
 * @param world The world to get the cell from.
 * @param x The x coordinate of the cell.
 * @param y The y coordinate of the cell.
 * @return `enum CellState` The state of the cell (ALIVE or DEAD).
 */
enum CellState gol_get_cell_state(struct World *world, uint32 x, uint32 y);

/**
 * @brief Run a step of the Game of Life simulation.
 *
 * @param world The world to run the step on.
 */
void gol_run_step(struct World *world);

#endif // CONWAY_H