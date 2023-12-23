#include "function.h"

/**
 * @file computer.c 
 *computer fonctions 
 * @Author Lucas Bezamat
*/

/**
 * @brief Represents the computer's action of shooting at the player's grid.
 * @param gridde A pointer to the player's game grid.
 * @param x The x dimension of the player's game grid.
 * @param y The y dimension of the player's game grid.
 * @details This function allows the computer to randomly choose a cell in the player's grid to shoot at, marking it appropriately.
 */
struct boat* init_Boat_ordi(int x, int y, struct grid* gridde) {


    struct boat* head = NULL;
    struct boat* current = NULL;
    int k;

    for (int i = 1; i <= nb_Boat; i++) {
        struct boat* copie = malloc(sizeof(struct boat));

        if (copie == NULL) {
            printf("Error allocating memory\n");
            exit(1);
        }

        copie->size_b = i;
        

        int x_sh = -1;
        int y_sh = -1;
        int ori = -1;

        do {
            srand(time(NULL));
            x_sh = rand() % (tab_size - i + 1);
            y_sh = rand() % (tab_size - i + 1);
            ori = rand() % 2 + 1;

            if (ori == 1) {
                while (x_sh < 0 || x_sh + i - 1 >= x) {
                    x_sh = rand() % (tab_size - i + 1);
                }

                while (y_sh < 0 || y_sh >= y) {
                    y_sh = rand() % (tab_size - i + 1);
                }
            } else {
                while (x_sh < 0 || x_sh >= x) {
                    x_sh = rand() % (tab_size - i + 1);
                }

                while (y_sh < 0 || y_sh + i - 1 >= y) {
                    y_sh = rand() % (tab_size - i + 1);
                }
            }

            copie->x = x_sh;
            copie->y = y_sh;
            copie->orientation = ori;
            copie->next = NULL;

            if (i == 1) {
                head = copie;
                current = head;
            } else {
                current->next = copie;
                current = current->next;
                current->next=NULL;
            }

            k = iscollision_ordi(copie, gridde);

            if (k == 1) {
                gridde = put_In(copie, gridde);
            }
        } while (k == 0);
    }

    return head;
}
/**
 * @brief Make the computer in a grid 
 * @param gridde A pointer to the player's game grid.
 * @param x The x dimension of the player's game grid.
 * @param y The y dimension of the player's game grid.
 * @details this function make the computer dont shoot at the same place that it shoots before 
 */

void shoot_ordi(struct grid* gridde, int x, int y) {
    
    int x_sh = -100;
    int y_sh = -100;

    do {

            srand(time(NULL));
            x_sh = rand()%tab_size;
            y_sh = rand()%tab_size; 
      
    } while (gridde->board[x_sh][y_sh] == WATER_SHOT || gridde->board[x_sh][y_sh] == WRECK);

    if (gridde->board[x_sh][y_sh] == WATER) {
        
        gridde->board[x_sh][y_sh] = WATER_SHOT;
    } else {
        
        gridde->board[x_sh][y_sh] = WRECK;
    }


}

/**
 * @brief Tell if there is a collision ( without printf for user experience )
 * @param gridde A pointer to the player's game grid.
 * @param boatt boatt A pointer to the player's boatts list.
 * @details permits to the computze to put well its piece 
 */

int iscollision_ordi(struct boat* boatt, struct grid* gridde) {
    if (boatt == NULL || gridde == NULL) {
    
        
        return -1;
    }

    int i;
    int x, y;

    if (boatt->orientation == 1 ) {
        for (i = 0; i < boatt->size_b; i++) {
     

           
            if (gridde->board[boatt->x + i][boatt->y] == BOAT) {
                
                return 0;
            }
        }
    } else if (boatt->orientation == 2) {
        for (i = 0; i < boatt->size_b; i++) {
    
            if (gridde->board[boatt->x][boatt->y + i] == BOAT) {
               
                return 0;
            }
        }
    }
    else {  
    return 0 ; }

   
    return 1;
}