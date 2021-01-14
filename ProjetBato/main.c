/**=====================================================================================================================
 * \file      ProjetBato.c
 * \author    <Florian Duruz>
 * \version   <0.1>
 * \date      <18-12-2020>
 * \brief     <this is "le Projet Bato" a naval battle>
 *
 =====================================================================================================================*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

//Tile Definition
#define WATER 20       //water tiles
#define ALPHAGRID 21   //Alphabet controler on the grid (A > Z)
#define NUMGRID 22     //Number controler on the grid (1 > 10)
#define EMPTYGRID 23   //Top left corner of the grid
#define HITGRID 24     //Hit on the grid
#define MISSGRID 25    //Miss on the grid
#define SINKGRID 26    //Sink on the grid

//Ships definition
#define SHIP5L 5   //ship 5 tiles length
#define SHIP2L 1  //ship 2 tiles length
#define SHIP3L1 2  //first ship 3 tiles length
#define SHIP3L2 3   //second ship 3 tiles length
#define SHIP4L 4   //ship 4 tiles length

/**
 *
 * \brief modeEtat : (State Machine) Define which function the programme is running
 *
 */
int modeEtat = 0;

/**=====================================================================================================================
 *
 * \brief emptyBuffer, use after a scanf function to clear the stored value
 *
 =====================================================================================================================*/


void emptyBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

FILE* openFile(FILE* file, char* name, char* mode)
{
    file = NULL;
    file = fopen(name, mode);
    if(file == NULL)
    {
        printf("Could not open a file!\n");
        exit(1);
    }
    else
    {
        printf("File was opened/created successfully!\n\n");
    }

    return file;
}
/**=====================================================================================================================
 *
 *\brief Aide, display the rules of the game and how we play it
 *\return Void
 *
 =====================================================================================================================*/
void Aide()
{
    char quitAide = 'z';

    printf("\nAide du jeu : Bataille Navale\n");
    printf("\nBienvenu dans la bataille navale,\nLe principe est simple, séléctionnez la case de votre choix pour tirer sur un bateau,");
    printf("\nPour gagner il vous faudra abattre les 5 bateaux en jeu.\n");
    printf("\nListe des indicateurs sur la grille du jeu");
    printf("\n~ : Case vierge");
    printf("\n0 : Tir manqué");
    printf("\nx : Bateau touché");
    printf("\nc : Bateau coulé");
    printf("\nPressez <q> pour quitter:");


    while (modeEtat == 2 && quitAide != 'q')
    {
        int res = scanf("%c", &quitAide);
        if (res == 0)
        {
            emptyBuffer();
        }

        if (quitAide == 'q')
        {
            modeEtat = 0;
        }
    }
    modeEtat = 0;
}
//=====================================================================================================
void scores()
{
    char quitAide = 'z';
    char pseudo[] = "noname";
    int score=0;
    FILE* file;
    file = openFile(file,"P:\\FPA\\MA20\\ProjetBato_Ma20\\NavalBattle_DuruzFlorian\\ProjetBato\\Scores.txt", "r");
    while (!feof(file))
    { /* check for end-of-file*/
        fscanf(file, "%s:%d", &pseudo, &score);
        printf("%s:%d\n", pseudo, score);
        
        //printf("%s:%d\n", pseudo, score);
    }

    while (modeEtat == 3 && quitAide != 'q')
    {
        int res = scanf("%c", &quitAide);
        if (res == 0)
        {
            emptyBuffer();
        }

        if (quitAide == 'q')
        {
            fclose(file);
            modeEtat = 0;
        }
    }
    modeEtat = 0;
}

/*
 while (!feof(input_file)) { /* check for end-of-file

if(fscanf(input_file, "%d;%d;%s", &range_start, &range_end, range_name) != 3) {
break; // Something weird happened on this line, so let's give up
else {
printf("I got the following numbers: %d, %d, %s\n", range_start, range_end, range_name);
}
}
 */

//=====================================================================================================

/*
void loadGrid()
{
    FILE* file;
    file = openFile(file,"P:\\FPA\\MA20\\TestTXT\\testGrid2.txt", "r");

    char charFile;
    int temp, colonne = 0, ligne = 1;
    int arr[ligne][colonne];
    //calculating the no. of rows and columns in the text file
    do
    {
        charFile = fgetc (file);
        //printf("%c", charFile);
        if((temp != 2) && (charFile == ' ' || charFile == '\n'))
        {
            colonne++;
        }

        if(charFile == '\n')
        {
            temp =2;
            ligne++;
        }
    } while (charFile != EOF);

    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            arr[i][j] = 0;
        }
    }

    rewind(file);
    //printf("ligne = %d; colonne = %d\n", ligne, colonne);

    for(int i=0; i < ligne; i++)
    {
        for(int j=0; j < colonne; j++)
        {
            charFile = fgetc (file);
            if (charFile != ' ' && charFile != '\n')
            {
                arr[i][j] = (int)charFile - 48; // see ASCII table
                printf("%d", arr[i][j]);

            }
            else if (charFile == ' ')
            {
                printf(" ");
                j -= 1;
            }
            else
            {
                j -= 1;
            }
        }
        printf("\n");
    }
}
*/
 /**====================================================================================================================
  *
  * \brief updateGrid - update the grid depending of the coordinate (ligne, colonne) and display it
  * \param ligne - ligne in the game grid
  * \param colonne - row in the game grid
  * \param grid - Game Grid table
  * \return void
  *
  ====================================================================================================================*/

void updateGrid(int ligne, int colonne,int grid[ligne][colonne])
{
    char Alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    /*================================================
     * grid take a value according to the value of the vector
     * 0 =top left of the grid
     * 1 = A-Z controler Value
     * 2 = TOP controler number value
     * 3 = Water Tile
     * 4 = HIT
     * 5 = Sink
     * 6 = Miss
    ================================================*/
    int vide = EMPTYGRID;
    int number = NUMGRID;
    int letter = ALPHAGRID;
    int hit = HITGRID;
    int sink = SINKGRID;
    int miss = MISSGRID;

    for (int i = 0; i < ligne ; ++i)
    {
        for (int j = 0; j < colonne; ++j)
        {

            if (grid[i][j] == vide)
            {
                printf(" ");
            }
            else if (grid[i][j] == number)
            {
                printf("%3d", j); // Grid Number 1 -> 10
            }
            else if (grid[i][j] == letter)
            {
                printf("%c", Alphabet[i]); // Grid Letter A -> J
            }
            else if (grid[i][j] == hit)
            {
                char hitMark = 'x';
                printf("%3c", hitMark); // Hit Mark Define by x
            }
            else if (grid[i][j] == sink)
            {
                char sinkMark = 'c';
                printf("%3c", sinkMark); // Sink Grid Mark
            }
            else if (grid[i][j] == miss)
            {
                char missMark = '0';
                printf("%3c", missMark); // Miss Grid Mark
            }
            else
            {
                char water = '~';
                printf("%3c", water); // Water Grid Mark
            }
        }
        putchar('\n');
    }
}

/**=====================================================================================================================
 *
 * \brief alphabetEntryChecker - Check if the player gace a correct entry for the alphabet
 * \param choiceAlpha - Character enter by the player
 * \param alphabet - alphabet table
 * \param ligne - grid line
 * \return true or false
 *
 =====================================================================================================================*/
bool alphabetEntryChecker(char choiceAlpha,char alphabet[], int ligne)
{
    /*
     * Go throught the alphabet table
     * Make +1 if the letter is within the Table
     * if the counter is equal to the total of the alphabet table: the letter enter by the player is not correct
     */
    int compteurAlpha = 0;
    for (int i = 0; i < ligne; ++i)
    {
        if (alphabet[i] != choiceAlpha)
        {
            compteurAlpha = compteurAlpha+1;
        }
    }
    if (compteurAlpha == ligne)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//=========================================================================

void scoreRegister(char pseudo[], int score)
{
    FILE* file;
    file = openFile(file,"P:\\FPA\\MA20\\ProjetBato_Ma20\\NavalBattle_DuruzFlorian\\ProjetBato\\Scores.txt", "a+");
    fputs(pseudo, file);
    fputs(" ", file);
    fprintf(file, "%d", score);
    fputs("\n",file);


    fclose (file);
}



//=========================================================================
/**=====================================================================================================================
 *
 * \brief jeu - "Main" play function,
 * \return void
 *
 =====================================================================================================================*/

void jeu()
{
    bool QuitGame = false;
    int score = 0;


    emptyBuffer();
    //Size of the grid
    //Row
    int ligne = 11;
    //column
    int colonne = 11;

    char alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    char choiceAlpha = 'z';
    int choiceNum = 0;

    //Pseudo Part
    bool pseudoChoose = false;
    char pseudo[] = "noName";
    while (pseudoChoose == false)
    {
        printf("\nBienvenu dans la Bataille navale, Veuillez entrer un pseudo:\n");
        scanf("%s", &pseudo);
        printf("\nVotre pseudo est %s\n", pseudo);
        emptyBuffer();
        pseudoChoose = true;
    }


    //Player Grid View
    int grid[ligne][colonne];
    //Generate a random number for grid selection
    int gridChoice = 0;
    //Adjust the number to the number of grid available
    int minGridChoice = 1;
    int maxGridChoice = 5;
    if (gridChoice == 0)
    {
        srand(time(0));
        gridChoice = (rand() %(maxGridChoice - minGridChoice + 1)) + minGridChoice;
        printf("GRID CHOSEN = %d\n", gridChoice);
    }
    //==========================================================================================================
    //Charge Corresponding grid
    //==========================================================================================================

    FILE* file;
    switch (gridChoice)
    {
        case 1:
            file = openFile(file,"P:\\FPA\\MA20\\ProjetBato_Ma20\\NavalBattle_DuruzFlorian\\ProjetBato\\GameGrid\\Grid1.txt", "r");
            break;
        case 2:
            file = openFile(file,"P:\\FPA\\MA20\\ProjetBato_Ma20\\NavalBattle_DuruzFlorian\\ProjetBato\\GameGrid\\Grid2.txt", "r");
            break;
        case 3:
            file = openFile(file,"P:\\FPA\\MA20\\ProjetBato_Ma20\\NavalBattle_DuruzFlorian\\ProjetBato\\GameGrid\\Grid3.txt", "r");
            break;
        case 4:
            file = openFile(file,"P:\\FPA\\MA20\\ProjetBato_Ma20\\NavalBattle_DuruzFlorian\\ProjetBato\\GameGrid\\Grid4.txt", "r");
            break;
        case 5:
            file = openFile(file,"P:\\FPA\\MA20\\ProjetBato_Ma20\\NavalBattle_DuruzFlorian\\ProjetBato\\GameGrid\\Grid5.txt", "r");
            break;
    }

    char charFile;
    int shipGrid[ligne-1][colonne-1];
    rewind(file);
    //printf("ligne = %d; colonne = %d\n", ligne, colonne);

    for(int i=0; i < ligne-1; i++)
    {
        for(int j=0; j < colonne-1; j++)
        {
            charFile = fgetc (file);
            if (charFile != ' ' && charFile != '\n')
            {
                shipGrid[i][j] = (int)charFile - 48; // see ASCII table
                printf("%d", shipGrid[i][j]);

            }
            else
            {
                j -= 1; // "\n" on the file
            }
        }
        printf("\n");
    }
    //==========================================================================================================


    //=================================================================
    /*
               1  2  3  4  5  6  7  8  9  10
    *
    *   a(1)   p  p  p  p  p  -  -  -  -  -
    *   b(2)   -  -  -  -  -  -  -  -  -  -
    *   c(3)   -  -  -  -  -  -  -  c  -  -
    *   d(4)   -  -  -  s  s  s  -  c  -  -
    *   e(5)   -  -  -  -  -  -  -  c  -  -
    *   f(6)   -  s  -  -  -  -  -  c  -  -
    *   g(7)   -  s  -  -  -  -  -  -  -  -
    *   h(8)   -  s  -  -  -  t  -  -  -  -
    *   i(9)   -  -  -  -  -  t  -  -  -  -
    *   j(10)  -  -  -  -  -  -  -  -  -  -
    */


    bool victory = false;
    bool alphabetChecker = false;
    bool numChecker = false;

    int shipSunk = 0; // number represente the ship sunk
    // Battleship
    int ship5L = SHIP5L; // "5" on the grid
    int ship5LLife = 5;
    bool ship5LSink = false;
    //cruiser
    int ship3L1 = SHIP3L1; // "2" on the grid
    int ship3L1Life = 3;
    bool ship3L1Sink = false;
    //torpedo
    int ship2L = SHIP2L; // "1" on the grid
    int ship2LLife = 2;
    bool ship2LSink = false;
    //Cruiser 2
    int ship3L2 = SHIP3L2; // "3" on the grid
    int ship3L2Life = 3;
    bool ship3L2Sink = false;

    int ship4L = SHIP4L; // "4" on the grid
    int ship4LLife = 4;
    bool ship4LSink = false;
    //===============================================================================================================================================

    //Initialize the player grid

    for(int a=0; a < ligne; a++)
    {
        for(int b=0; b < colonne; b++)
        {
            if (a == 0 && b == 0)
            {
                grid[a][b] = EMPTYGRID; // Top Left Corner of the grid : nothing to display
            }
            else if (a == 0)
            {
                grid[a][b] = NUMGRID; // Define Number Controler on the Grid (1 -> 10)

            }
            else if (b == 0)
            {
                grid[a][b] = ALPHAGRID; // Define Letter (A->J) Controler on the Grid

            }
            else
            {
                grid[a][b] = WATER; // Define the water tile on the grid
            }
        }

    }
    updateGrid(ligne, colonne, grid);
    printf("\nChoisissez la case a abattre:\n");
    printf("\nPressez <q> pour quitter:\n");
    putchar('\n');
    //===============================================================================================================================================
    while (modeEtat == 1)
    {
        if(victory == false)
        {
            choiceAlpha = 'z';
            choiceNum = 0;

            printf("\nVeuillez choisir une lettre entre <a> et <j>");
            while (alphabetChecker == false)
            {
                int resAlpha = scanf("%c", &choiceAlpha);
                if (resAlpha == 0)
                {
                    emptyBuffer();
                    printf("\nChoix non valide, Veuillez choisir une lettre entre <a> et <j>");
                }
                    //Check if player want to Quit
                else if (choiceAlpha == 'q')
                {
                    fclose(file);
                    scoreRegister(pseudo,score);
                    modeEtat = 0;
                    alphabetChecker = true;
                    numChecker = true;
                }
                else
                {
                    //Check if the choice is between A-J

                    if (alphabetEntryChecker(choiceAlpha,alphabet,ligne) == true)
                    {
                        emptyBuffer();
                        printf("\nVeuillez choisir un chiffre entre <1> et <10>");
                        alphabetChecker = true;
                    }
                    else
                    {
                        emptyBuffer();
                        printf("\nChoix non valide, Veuillez choisir une lettre entre <a> et <j>");
                    }
                }
            }
            while (numChecker == false)
            {
                int resNum = scanf("%d", &choiceNum);
                if (resNum == 0)
                {
                    emptyBuffer();
                    printf("\nChoix non valide, Veuillez choisir un chiffre entre <1> et <10>");
                }
                else if (choiceNum > 0 && choiceNum < 11)
                {
                    numChecker = true;
                }
                else
                {
                    emptyBuffer();
                    printf("\nChoix non valide, Veuillez choisir un chiffre entre <1> et <10>");
                }
            }
            if(numChecker == true && alphabetChecker == true)
            {
                for (int j = 0; j < ligne; ++j)
                {
                    int shotLigne = 0;
                    //Search for the line corresponding to the letter choose by the player
                    if (alphabet[j] == choiceAlpha)
                    {
                        int hit = HITGRID;
                        int miss = MISSGRID;
                        int sink = SINKGRID;
                        int shipShoot = 0;

                        shotLigne = j;
                        //IL FAUT FAIRE -1 CAR LE GRID SHIP est plus petit!
                        if (shipGrid[shotLigne-1][choiceNum-1] != 0 && shipGrid[shotLigne-1][choiceNum-1] != hit && grid[shotLigne][choiceNum] != hit && grid[shotLigne][choiceNum] != sink)
                        {
                            //printf("Shigridu %d", shipGrid[shotLigne-1][choiceNum-1]);
                            //Indication for ship Hit
                            grid[shotLigne][choiceNum] = HITGRID;
                            shipShoot = shipGrid[shotLigne-1][choiceNum-1];
                            switch (shipShoot)
                            {
                                case SHIP5L:
                                    ship5LLife -= 1;
                                    if (ship5LLife <= 0)
                                    {
                                        shipSunk = SHIP5L;
                                        ship5LSink = true;
                                    }
                                    break;
                                case SHIP4L:
                                    ship4LLife -= 1;
                                    if (ship4LLife <= 0)
                                    {
                                        shipSunk = SHIP4L;
                                        ship4LSink = true;
                                    }
                                    break;
                                case SHIP3L2:
                                    ship3L2Life -= 1;
                                    if (ship3L2Life <= 0)
                                    {
                                        shipSunk = SHIP3L2;
                                        ship3L2Sink = true;
                                    }
                                    break;
                                case SHIP3L1:
                                    ship3L1Life -= 1;
                                    if (ship3L1Life <= 0)
                                    {
                                        shipSunk = SHIP3L1;
                                        ship3L1Sink = true;
                                    }
                                    break;
                                case SHIP2L:
                                    ship2LLife -= 1;
                                    if (ship2LLife <= 0)
                                    {
                                        shipSunk = SHIP2L;
                                        ship2LSink = true;
                                    }
                                    break;
                                default:
                                    shipSunk = 0;
                                    break;
                            }
                            //==========================================================================================
                            /*
                             * Select which ship is sunk and modify the value on the grid
                             */
                            //=========================================================================================
                            if(shipSunk != 0)
                            {
                                for (int i = 0; i < ligne; ++i)
                                {
                                    for (int k = 0; k < colonne; ++k)
                                    {
                                        if(shipGrid[i][k] == shipSunk && grid[i+1][k+1] == HITGRID)
                                        {
                                            grid[i+1][k+1] = SINKGRID;
                                        }
                                    }
                                }
                                shipSunk = 0;
                                printf("\nTouché coulé!\n");
                            }
                            else
                            {
                                printf("\nTouché!\n");
                            }

                            updateGrid(ligne, colonne, grid);
                        }
                        else if (grid[shotLigne][choiceNum] == hit || grid[shotLigne][choiceNum] == sink || grid[shotLigne][choiceNum] == miss)
                        {
                            printf("\nvous avez déjà tiré ici.");
                        }
                        else
                        {
                            // 6 Define a Miss Hit in the Grid
                            grid[shotLigne][choiceNum] = MISSGRID;
                            updateGrid(ligne, colonne, grid);
                            printf("\nRaté!");
                        }
                        printf("\nChoisissez la case a abattre:");
                        printf("\nPressez q pour quitter:\n");
                        emptyBuffer();
                    }
                }
                alphabetChecker = false;
                numChecker = false;
            }

            if (ship5LSink == true && ship3L1Sink == true && ship2LSink == true && ship3L2Sink == true && ship4LSink == true)
            {
                printf("\nVous avez gagné !\n");
                printf("Retour au menu\n");
                victory = true;
                fclose(file);
                modeEtat = 0;
            }
        }


    }
}

/**=====================================================================================================================
 *
 * \brief main - Main menu, State machine system
 * \return int
 *
===================================================================================================================== */

int main()
{
    setbuf(stdout,0);
    SetConsoleOutputCP(65001);
    /*===========================

    * State Machine
    * States:
    * 0/Default : Main Menu - function main()
    * 1         : Play - function jeu()
    * 2         : Help menu - function Aide()
    * 5         : Quit the Game

    ===========================*/
    int choixMenu = 0;
    int previousState = 0; // mechanical button to avoid the menu to display twice when coming back from the game


    printf("\nBienvenu dans La bataille Navale");
    printf("\n1 : JOUER");
    printf("\n2 : AIDE DU JEU");
    printf("\n3 : SCORES");
    printf("\n5 : QUITTER");
    printf("\nChoisissez le mode voulu parmis en entrant le chiffre correspondant ci-dessus.");
    printf("\nVotre Choix:");

    while (modeEtat == 0 && choixMenu == 0)
    {
        if (previousState != 0)
        {
            previousState = 0;
            printf("\nBienvenu dans La bataille Navale");
            printf("\n1 : JOUER");
            printf("\n2 : AIDE DU JEU");
            printf("\n3 : SCORES");
            printf("\n5 : QUITTER");
            printf("\nChoisissez le mode voulu parmis en entrant le chiffre correspondant ci-dessus.");
            printf("\nVotre Choix:");
        }
        int res = scanf("%d", &choixMenu);

        if (res == 0)
        {
            emptyBuffer();
        }

        switch (choixMenu)
        {
            case 0:
                previousState = 0;
                modeEtat = 0;
                choixMenu = 0;
                break;
            case 1: //Play Mode
                previousState = 1;
                modeEtat = 1;
                jeu();
                choixMenu = 0;
                break;
            case 2://Help Mode
                previousState = 2;
                modeEtat = 2;
                Aide();
                choixMenu = 0;
                break;
            case 3://Score Mode
                previousState = 2;
                modeEtat = 3;
                scores();
                choixMenu = 0;
                break;
            case 5:
                printf("Bye!");
                return 1;
            default:// mode "Main Menu
                modeEtat = 0;
                choixMenu = 0;
                break;
        }

    }
    return 0;
}
