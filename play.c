#include "function.h"

/**
 * @file play.c 
 * principal file of the program
 * @Author Lucas Bezamat
*/

/**
 * @brief the display alive function
 * 
 * it aims to show and return if a bot a bot is wreck or it is destroyed 
 */

 int  display_alive(struct boat* boat1, struct grid* board1) {
    int w = 0;

    if (boat1->orientation == 1) {

        for (int i = 0; i < boat1->size_b; i++) {
           
            if (board1->board[boat1->x + i][boat1->y] != BOAT) {
                printf("Your boat is wrecked at coordinates (%d, %d)\n", boat1->x + i, boat1->y);
                w++;
            }
        }
    } else {
        for (int i = 0; i < boat1->size_b; i++) {
           
            if (board1->board[boat1->x][boat1->y + i] != BOAT) {
                printf("Your boat is wrecked at coordinates (%d, %d)\n", boat1->x, boat1->y + i);
                w++;
            }
        }
    }

    printf("Hits: %d\n", w);

    if (w == boat1->size_b) {
        printf("Your boat of size %d is fully wrecked.\n", boat1->size_b);
        return 1;
    }

    return 0;
}
/**
 * @brief Clears the input buffer.
 * 
 * This function reads characters from the input buffer until a newline ('\n') 
 * We aim to delete all miss or intentional problematic input that can perturb all the program
 */

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

} 

/**
 * @brief the display tab function
 * 
 * it aims todisplay all the ennemy that without his boats and with colors 
 */

void display_tab(struct grid* gridde, int x, int y ) {
                
                printf("\nBOT|" );
             for(int w = 0 ; w<y ; w++){
                    printf("%d|", w);
                } 
                printf("\n");            
    for (int i = 0; i < x; i++) {
        printf("| %d|" , i );
        for (int j = 0; j < y; j++) {

            if (gridde->board[i][j] == WATER) {
                printf(ANSI_COLOR_RESET " |" ANSI_COLOR_RESET);
            }
            else if (gridde->board[i][j] == WATER_SHOT) {
                printf(ANSI_COLOR_RED "X|" ANSI_COLOR_RESET);
            }
            else if (gridde->board[i][j] == WRECK) {
                printf(ANSI_COLOR_YELLOW "O|" ANSI_COLOR_RESET);
            }
            else {
                printf(ANSI_COLOR_RESET " |" ANSI_COLOR_RESET);

            }                   
        }
        printf("\n");
    }
}

/**
 * @brief the display your tab function
 * 
 * it aims to display your tab complete with different color  
 */
void display_your_tab (struct grid* gridde, int x, int y ) {
                
                printf("\nYOU|");
             for(int w = 0 ; w<y ; w++){
                    printf("%d|", w);
                } 
                printf("\n");
            
    for (int i = 0; i < x; i++) {
        printf("| %d|" , i );

        for (int j = 0; j < y; j++) {

        if (gridde->board[i][j] == WATER) {
            printf(ANSI_COLOR_RESET " |" ANSI_COLOR_RESET);
        }
        else if (gridde->board[i][j] == WATER_SHOT) {
            printf(ANSI_COLOR_RED "X|" ANSI_COLOR_RESET);
        }
        else if (gridde->board[i][j] == WRECK) {
            printf(ANSI_COLOR_YELLOW "O|" ANSI_COLOR_RESET);
        }
        else if (gridde->board[i][j] == BOAT) {
            printf(ANSI_COLOR_GREEN "B|" ANSI_COLOR_RESET);
        }
                    
        }
        printf("\n");
    }
}

/**
 * @brief the shoot function
 * 
 * it aims to make the user choose the cell where he will shoot with condition ( he cant shoot where he shoots before and cant shoot out of the grid)
 */
void shoot(struct grid* gridde, int x, int y) {
    printf("This is your opponent's grid:\n");
    display_tab(gridde, x, y);

    int x_sh = -1;
    int y_sh = -1;

    do {
        printf("Choose your line (0 to %d):\n", x - 1);
        while (scanf("%d", &x_sh) != 1 || x_sh < 0 || x_sh >= x || getchar() != '\n') {
            clearInputBuffer();
            printf("Invalid input. Choose your line (0 to %d):\n", x - 1);
        }

        printf("Choose your column (0 to %d):\n", y - 1);
        while (scanf("%d", &y_sh) != 1 || y_sh < 0 || y_sh >= y || getchar() != '\n') {
            clearInputBuffer();
            printf("Invalid input. Choose your column (0 to %d):\n", y - 1);
        }

        if (gridde->board[x_sh][y_sh] == WATER_SHOT || gridde->board[x_sh][y_sh] == WRECK) {
            printf("You already shot at this location. Choose again.\n");
        }

    } while (gridde->board[x_sh][y_sh] == WATER_SHOT || gridde->board[x_sh][y_sh] == WRECK);

    if (gridde->board[x_sh][y_sh] == WATER) {
        printf("\nMissed! There's nothing here.\n");
        gridde->board[x_sh][y_sh] = WATER_SHOT;
    } else {
        printf("\nHit! You've hit an opponent's boat.\n");
        gridde->board[x_sh][y_sh] = WRECK;
    }

    printf("Updated opponent's grid:\n");
    display_tab(gridde, x, y);
}

/**
 * @brief the winner function
 * 
 * it counts the wreck cell and if it is equal to 15 return 1 that means the user win 
 */
int see_winner(struct grid* gridde , int x , int  y ){
    int k  =   0 ; 
    for (int i = 0; i < x; i++) {
      
        for (int j = 0; j < y; j++) {
            if( gridde->board[i][j] == WRECK ){
             k++ ; 
            }     
        }     
    }
    if (k == 15)
    {
        return 1 ;
    }
    else {
        return 0 ; 
    } 
}

/**
 * @brief the  put in  function 
 * 
 * this function aims to put a new boat in the user grid  
 */
struct grid* put_In(struct boat* boatt, struct grid* gridde) {
    if (boatt->orientation == 1) {
        for (int i = 0; i < boatt->size_b; i++) {
            gridde->board[boatt->x + i][boatt->y] = BOAT;
        }
    } else {
        for (int i = 0; i < boatt->size_b; i++) {
            gridde->board[boatt->x][boatt->y + i] = BOAT;
        }
    }
    
    return gridde;
    
}
/**
 * @brief tthis is the menu to see if a bot is wreck
 * 
 *
 */
void choosetoseewreck(struct boat* boat1, struct grid* board1) {
    int option;

    do {
        printf("\nSaisissez votre option:\n");
        printf("Choose a number between 1 and 5, or 6 to stop\n");

        while (scanf("%d", &option) != 1 || (option < 1 || option > 6) || getchar() != '\n') {
            clearInputBuffer();
            printf("Invalid input. Choose a number between 1 and 5, or 6 to stop\n");
        }

        if (option >= 1 && option <= 5) {
            struct boat* current = boat1;
            for (int i = 1; i < option; i++) {
                if (current != NULL) {
                    current = current->next;
                } else {
                    printf("Invalid option. Please choose a valid option.\n");
                    break;
                }
            }

            if (current != NULL) {
                int aliv = display_alive(current, board1);  
                if (aliv == 0) {
                 
                    printf("Your boat is alive.\n");
                } else {
                    printf("Your boat is broken (%d hits).\n", aliv);
                   
                }
            }
        } else if (option == 6) {
            return;
        } else {
            printf("Invalid option. Please choose a valid option.\n");
        }

    } while (option != 6);
}

/**
 * @brief help the user to initialize his boat  and put it on his grid
 * 
 * with conditions  
 */

struct boat* init_Boat(int x, int y, struct grid* gridde) {
    struct boat* head = NULL; // Nouvelle variable pour conserver le premier bateau
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
            printf("Choose your orientation: 1 for vertical | 2 for horizontal\n");
            while (scanf("%d", &ori) != 1 || (ori != 1 && ori != 2) || getchar() != '\n') {
                clearInputBuffer();
                printf("Invalid input. Choose your orientation: 1 for vertical | 2 for horizontal\n");
            }

            if (ori == 1) {
                printf("Choose your line (0 to %d):\n", x - 1);
                while (scanf("%d", &x_sh) != 1 || (x_sh < 0 || x_sh + i - 1 >= x) || getchar() != '\n') {
                    clearInputBuffer();
                    printf("Invalid input. Choose your line (0 to %d):\n", x - 1);
                }

                printf("Choose your column (0 to %d):\n", y - 1);
                while (scanf("%d", &y_sh) != 1 || (y_sh < 0 || y_sh >= y) || getchar() != '\n') {
                    clearInputBuffer();
                    printf("Invalid input. Choose your column (0 to %d):\n", y - 1);
                }
            } else {
                printf("Choose your line (0 to %d):\n", x - 1);
                while (scanf("%d", &x_sh) != 1 || (x_sh < 0 || x_sh >= x) || getchar() != '\n') {
                    clearInputBuffer();
                    printf("Invalid input. Choose your line (0 to %d):\n", x - 1);
                }

                printf("Choose your column (0 to %d):\n", y - 1);
                while (scanf("%d", &y_sh) != 1 || (y_sh < 0 || y_sh + i - 1 >= y) || getchar() != '\n') {
                    clearInputBuffer();
                    printf("Invalid input. Choose your column (0 to %d):\n", y - 1);
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
            current->next = copie;
            current = current->next;
        
    }

    return head; // Retournez le pointeur vers le premier bateau de la liste
}

/**
 * @brief The global menu for the game.
 * 
 * This function serves as the central hub for the game, allowing the user to:
 * - Play the game,
 * - Create boats and place them on the board,
 * - Shoot at the enemy,
 * - Make the computer take its turn,
 * - Declare the winner.
 * 
 * It manages game flow, including initializing game structures, taking user input for game options, and 
 * handling the main game loop until a winner is declared.
 */

void menu_global() {
int num_joueur  = 1  ;
int win = -1 ; 
struct boat* boat1  = malloc(sizeof(struct boat));    
struct boat* boat2  = malloc(sizeof(struct boat));
struct grid* board1 = malloc(sizeof(struct grid));
struct grid* board2 = malloc(sizeof(struct grid));
 if ( boat1== NULL || board1 == NULL || board2 == NULL || boat2 == NULL) {
        printf("erreur allocation mémoire ");
        exit(150);
    }

    board1->board = init_board(tab_size, tab_size);
    boat1 = init_Boat(tab_size , tab_size, board1);

    board2->board = init_board(tab_size, tab_size);
    boat2 = init_Boat_ordi( tab_size , tab_size, board2);

   
    do {
    printf("\n");

    printf("\nSaissiez votre option : \n");
    printf(" Write  1 for SHOOT 2 for display your grid  3 to display the ennemi grid 4 to see your wreck boat 5 to exit 6 to cheat \n" ); 
    int option ; 
   
        while (scanf("%d", &option) != 1 || getchar() != '\n') {
            clearInputBuffer();
            printf("Invalid input. Please enter a valid option.\n");
        }
        printf("\n");
        
        if (option == 1 ){
           shoot(board1 ,tab_size , tab_size);
           shoot_ordi(board1 , tab_size , tab_size );
        }
        else if (option == 2 ){
            display_your_tab(board1 , tab_size , tab_size);
              
        }
        else if (option == 3){  
            
            display_tab(board2 , tab_size, tab_size);  
           
        }
        else if (option == 4 ){    
             choosetoseewreck(boat1 , board1);    
        }
        else if (option == 5 ){    
            return ;
        }

        else if (option == 6 ){
        printf("enemy grid");
        display_your_tab(board2 , tab_size , tab_size);
        }
        else{
            printf("Tu t'es trompé de reve akhy \n");
           
        }
 
     
    if((win = see_winner(board1 , tab_size , tab_size)) == 1 ){
        printf("you loose");
    }
    else if ((win = see_winner(board2 , tab_size , tab_size)) == 1){
        printf("you WIN");
    }
    }while( win != 1 );
  
    return;
}

void free_memory(struct grid* board, struct boat* boats) {

    for (int i = 0; i < board->x; i++) {
        free(board->board[i]);
    }
    free(board->board);
    free(board);


    struct boat* current = boats;
    struct boat* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}



int** init_board(int x, int y) {
    int** gridde = (int**)malloc(y * sizeof(int*));
    if (gridde == NULL) {
        fprintf(stderr, "Error allocating memory for the grid.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < y; i++) {
        gridde[i] = (int*)malloc(x * sizeof(int));
        if (gridde[i] == NULL) {
            fprintf(stderr, "Error allocating memory for the grid row.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < x; j++) {
            gridde[i][j] = WATER; // Initialize all cells to water
        }
    }
    return gridde;
}




int isVictory(struct grid* gridde , int x , int y  ){

   
    for (int i = 0; i < x; i++) {
        
        for (int j = 0; j < y; j++) {
       
      if (gridde->board[i][j] == BOAT) {
            printf("There is no winner for now \n "); 
        }
                    
        }
      
    }
}



void free_grid(struct grid* board) {
    for (int i = 0; i < board->x; i++) {
        free(board->board[i]);
    }
    free(board->board);
    free(board);
}

int iscollision(struct boat* boatt, struct grid* gridde) {
    if (boatt == NULL || gridde == NULL) {
    
        printf("\nInvalid input pointers.\n");
        return -1;
    }

    int i;
    int x, y;

    if (boatt->orientation == 1 ) {
        for (i = 0; i < boatt->size_b; i++) {
      

            display_your_tab(gridde , tab_size, tab_size ); 
            if (gridde->board[boatt->x + i][boatt->y] == BOAT) {
                printf("\nCollision at coordinates (%d, %d).\n", x, y);
                return 0;
            }
        }
    } else if (boatt->orientation == 2) {
        for (i = 0; i < boatt->size_b; i++) {
    
            if (gridde->board[boatt->x][boatt->y + i] == BOAT) {
                printf("\nCollision at coordinates (%d, %d).\n", x, y);
                return 0;
            }
        }
    }
    else { printf("Invalid orientation "); 
    return 0 ; }

    printf("\nNo collision detected.\n");
    return 1;
}
/**
 * @brief display a list formatted of your boats this function help me to see the problems 
 *
 */
void display_boat(struct boat* boatt ){

    while (boatt != NULL){
        printf( " x = %d  | y = %d | ori = %d | size = %d | \n" , boatt->x , boatt->y , boatt->orientation , boatt->size_b ); 
    boatt = boatt->next;
    }
 
}

/**
 * @brief function that permit to secure the memory 
 *
 */
void free_boats(struct boat* boatt) {
    struct boat* current = boatt;
    struct boat* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}