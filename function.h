
/**
 * @file function.h
 * @brief This file prototypes of the game  and all the comment faire the functions
 * @Author Lucas Bezamat
 */
#ifndef FUNCTION_H



#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Color definitions for console output
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

// Game-specific definitions
#define nb_Boat 5 
#define tab_size 10 

/**
 * @enum CELL_TYPE
 * @brief Enumerates types of cells in the game grid.
 */
enum {
    WATER,       /**< Represents water cell */
    WATER_SHOT,  /**< Represents water cell that's been shot at */
    BOAT,        /**< Represents a cell occupied by a boat */
    WRECK        /**< Represents a wrecked part of a boat */
};

/**
 * @struct boat
 * @brief Represents a boat in the game.
 * @var boat::size_b Size of the boat.
 * @var boat::orientation Orientation of the boat; 1 for vertical, 0 for horizontal.
 * @var boat::x X-coordinate of the boat's position.
 * @var boat::y Y-coordinate of the boat's position.
 * @var boat::next Pointer to the next boat in a linked list.
 */

/**
 * @struct grid
 * @brief Represents the game grid.
 * @var grid::board 2D array representing the game board.
 * @var grid::x Width of the grid.
 * @var grid::y Height of the grid.
 */

/**
 * @struct jeu
 * @brief Represents the game state.
 * @var jeu::boate Pointer to the list of boats.
 * @var jeu::gridd Pointer to the game grid.
 */

// Function prototypes with brief descriptions

/**
 * @brief Checks if all boats on the grid have been sunk.
 * @param gridde Pointer to the game grid.
 * @param x Width of the grid.
 * @param y Height of the grid.
 * @return Returns 1 if all boats are sunk, otherwise returns 0.
 */
struct boat {
    int size_b;
    int orientation; // 1 means vertical 0 horizontal 
    int x;
    int y;
    struct boat* next;
};

struct grid {
    int** board;
    int x;
    int y;
};

struct jeu {
    struct boat*  boate;
    struct grid*  gridd;
};

int isVictory(struct grid* gridde, int x, int y );
int** init_board(int x, int y);
void display_tab(struct grid* gridde, int x, int y);
void display_your_tab(struct grid* gridde, int x, int y); 
void shoot(struct grid* gridde , int x, int y);
void shoott(struct grid* gridde, int x, int y);
int see_winner(struct grid* gridde, int x, int y);
void free_grid(struct grid* board);
int iscollision(struct boat* boatt, struct grid* gridde);
int iscollision_ordi(struct boat* boatt, struct grid* gridde);
struct grid* put_In(struct boat* boatt, struct grid* gridde);
void display_boat(struct boat* boatt);
void free_boats(struct boat* boatt);
int display_alive(struct boat* boat1, struct grid* board1);
void choosetoseewreck(struct boat* boat1, struct grid* board1);
void menu_global();
void free_memory(struct grid* board, struct boat* boats);
void shoot_ordi(struct grid* gridde, int x, int y);
struct boat* init_Boat(int x, int y, struct grid* gridde) ;
struct boat* init_Boat_ordi(int x, int y, struct grid* gridde);
#endif
