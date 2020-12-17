/**
 * @file      ProjetBato.c
 * @author    <Florian Duruz>
 * @version   <0.1>
 * @date      <18-12-2020>
 * @brief     <this is "le Projet Bato" a naval battle>
 *
 * @details    <More complete description>
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
/**
 * \brief modeEtat : (State Machine) Define which function the programme is running
 */
int modeEtat = 0;

void emptyBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//======================================================================================================
/**
 *
 *@brief Aide, display the rules of the game and how we play it
 *@return Void
 *
 */
//======================================================================================================
void Aide()
{
    char quitAide = 'z';

    //Text ICI
    printf("\nAide du jeu : Bataille Navale\n");
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
 /**
  * @brief updateGrid - update the grid depending of the coordinate (ligne, colonne) and display it
  * @param ligne - ligne in the game grid
  * @param colonne - row in the game grid
  * @param grid
  * @return void
  */
//=====================================================================================================
void updateGrid(int ligne, int colonne,int grid[ligne][colonne])
{
    char Alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    int vide = 0;
    int number = 1;
    int letter = 2;
    int hit = 4;
    int sink = 5;
    int miss = 6;

    for (int i = 0; i <ligne ; ++i)
    {
        for (int j = 0; j <colonne; ++j)
        {

            if (grid[i][j] == vide)
            {
                printf(" ");
            }
            else if (grid[i][j] == number)
            {
                printf("%3d", j);
            }
            else if (grid[i][j] == letter)
            {
                printf("%c", Alphabet[i]);
            }
            else if (grid[i][j] == hit)
            {
                char hitMark = 'x';
                printf("%3c", hitMark);
            }
            else if (grid[i][j] == sink)
            {
                char sinkMark = 'c';
                printf("%3c", sinkMark);
            }
            else if (grid[i][j] == miss)
            {
                char missMark = '0';
                printf("%3c", missMark);
            }
            else
            {
                char water = '~';
                printf("%3c", water);
            }
        }
        putchar('\n');
    }
}

//=====================================================================================================
/**
 * @brief jeu - "Main" play function,
 * @return void
 */
//=====================================================================================================
void jeu()
{
    bool QuitGame = false;
    emptyBuffer();
    //DIMENSION DE LA GRILLE
    //ligne
    int ligne = 11;
    //COLONNE
    int colonne = 11;

    char alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    char choiceAlpha = 'z';
    int choiceNum = 0;
    //Player Grid View
    int grid[ligne][colonne];

    //=================================================================
    //Init Ship Grid
    int shipGrid[ligne][colonne];
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
    bool alpha = false;
    bool num = false;
    // Battleship
    int pShip = 10;
    shipGrid[1][1] = pShip;
    shipGrid[1][2] = pShip;
    shipGrid[1][3] = pShip;
    shipGrid[1][4] = pShip;
    shipGrid[1][5] = pShip;
    bool pShipSink = false;
    //cruiser
    int cShip = 11;
    shipGrid[6][2] = cShip;
    shipGrid[7][2] = cShip;
    shipGrid[8][2] = cShip;
    bool cShipSink = false;
    //torpedo
    int tShip = 12;
    shipGrid[8][6] = tShip;
    shipGrid[9][6] = tShip;
    bool tShipSink = false;
    //Cruiser 2
    int cShip2 = 13;
    shipGrid[4][4] = cShip2;
    shipGrid[4][5] = cShip2;
    shipGrid[4][6] = cShip2;
    bool cShip2Sink = false;

    int bShip = 14;
    shipGrid[3][8] = bShip;
    shipGrid[4][8] = bShip;
    shipGrid[5][8] = bShip;
    shipGrid[6][8] = bShip;
    bool bShipSink = false;

    // initialize the ship grid
    for (int i = 0; i < ligne; ++i)
    {
        for (int j = 0; j < colonne; ++j)
        {
            if (shipGrid[i][j] != pShip && shipGrid[i][j] != cShip && shipGrid[i][j] != tShip && shipGrid[i][j] != cShip2 && shipGrid[i][j] != bShip)
            {
                shipGrid[i][j] = 0;
            }
        }
    }
    //=================================================================
    //Initialize the player grid
    for(int a=0; a < ligne; a++)
    {
        for(int b=0; b < colonne; b++)
        {
            if (a == 0 && b == 0)
            {
                grid[a][b] = 0;
            }
            else if (a == 0)
            {
                grid[a][b] = 1;

            }
            else if (b == 0)
            {
                grid[a][b] = 2;

            }
            else
            {
                grid[a][b] = 3;
            }
        }

    }
    updateGrid(ligne, colonne, grid);
    printf("\nChoisissez la case a abattre:\n");
    printf("\nPressez <q> pour quitter:\n");
    putchar('\n');

    while (modeEtat == 1)
    {
        /*
         * grid take a value according to the value of the vector
         * 0 =top left of the grid
         * 1 = A-Z controler Value
         * 2 = TOP controler number value
         * 3 = Water Tile
         * 4 = HIT
         */

        /*================================================
         *
         * Display the game grid
         * Display the selector controler part of the grid (A-Z; 1-15)
         *
         ================================================*/
        if(victory == false)
        {
            choiceAlpha = 'z';
            choiceNum = 0;

            printf("\nVeuillez choisir une lettre entre <a> et <j>");
            while (alpha == false)
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
                    modeEtat = 0;
                    alpha = true;
                    num = true;
                }
                else
                {
                    //Check if the choice is between a-j
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
                        emptyBuffer();
                        printf("\nChoix non valide, Veuillez choisir une lettre entre <a> et <j>");
                    }
                    else
                    {
                        emptyBuffer();
                        printf("\nVeuillez choisir un chiffre entre <1> et <10>");
                        alpha = true;
                    }
                }
            }
            while (num == false)
            {
                int resNum = scanf("%d", &choiceNum);
                if (resNum == 0)
                {
                    emptyBuffer();
                    printf("\nChoix non valide, Veuillez choisir un chiffre entre <1> et <10>");
                }
                else if (choiceNum > 0 && choiceNum < 11)
                {
                    num = true;
                }
                else
                {
                    emptyBuffer();
                    printf("\nChoix non valide, Veuillez choisir un chiffre entre <1> et <10>");
                }
            }
            if(num == true && alpha == true)
            {
                for (int j = 0; j < ligne; ++j)
                {
                    int shotLigne = 0;
                    //Search for the line corresponding to the letter choose by the player
                    if (alphabet[j] == choiceAlpha)
                    {
                        shotLigne = j;
                        if (shipGrid[j][choiceNum] != 0 && shipGrid[shotLigne][choiceNum] != 4 && grid[shotLigne][choiceNum] != 4 && grid[shotLigne][choiceNum] != 5)
                        {
                            //printf("test1\n%d\n", shipGrid[shotLigne][choiceNum]);

                            grid[shotLigne][choiceNum] = 4;
                            if (grid[1][1] == 4 && grid[1][2] == 4 && grid[1][3] == 4 && grid[1][4] == 4 && grid[1][5] == 4)
                            {
                                grid[1][1] = 5;
                                grid[1][2] = 5;
                                grid[1][3] = 5;
                                grid[1][4] = 5;
                                grid[1][5] = 5;
                                printf("\nTouché coulé!!!\n");
                                pShipSink = true;
                            }

                            else if (grid[6][2] == 4 && grid[7][2] == 4 && grid[8][2] == 4)
                            {
                                grid[6][2] = 5;
                                grid[7][2] = 5;
                                grid[8][2] = 5;
                                printf("\nTouché coulé!!!\n");
                                cShipSink = true;
                            }

                            else if (grid[8][6] == 4 && grid[9][6] == 4)
                            {
                                grid[8][6] = 5;
                                grid[9][6] = 5;
                                printf("\nTouché coulé!!!\n");
                                tShipSink = true;
                            }

                            else if (grid[4][4] == 4 && grid[4][5] == 4 && grid[4][6] == 4)
                            {
                                grid[4][4] = 5;
                                grid[4][5] = 5;
                                grid[4][6] = 5;
                                printf("\nTouché coulé!!!\n");
                                cShip2Sink = true;
                            }

                            else if (grid[3][8] == 4 && grid[4][8] == 4 && grid[5][8] == 4 && grid[6][8] == 4)
                            {
                                grid[3][8] = 5;
                                grid[4][8] = 5;
                                grid[5][8] = 5;
                                grid[6][8] = 5;
                                printf("\nTouché coulé!!!\n");
                                bShipSink = true;
                            }
                            else
                            {
                                printf("\nTouché!\n");
                            }

                            updateGrid(ligne, colonne, grid);
                        }
                        else if (grid[shotLigne][choiceNum] == 4 || grid[shotLigne][choiceNum] == 5 || grid[shotLigne][choiceNum] == 6)
                        {
                            printf("\nvous avez déjà tiré ici.");
                        }
                        else
                        {
                            grid[shotLigne][choiceNum] = 6;
                            updateGrid(ligne, colonne, grid);
                            printf("\nRaté!");
                        }
                        printf("\nChoisissez la case a abattre:");
                        printf("\nPressez q pour quitter:\n");
                        emptyBuffer();
                    }
                }
                alpha = false;
                num = false;
            }

            if (pShipSink == true && cShipSink == true && tShipSink == true && cShip2Sink == true && bShipSink == true)
            {
                printf("\nVOUS AVEZ GAGNEZ!\n");
                printf("Retour au menu\n");
                victory = true;
                modeEtat = 0;
            }
        }


    }
}

//=====================================================================================================
/**
 * @brief main - Main menu, State machine system
 * @return int
 */
//=====================================================================================================
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

    ===========================*/
    int choixMenu = 0;
    int previousState = 0;


    printf("\nBienvenu dans La bataille Navale");
    printf("\n1 : JOUER");
    printf("\n2 : AIDE DU JEU");
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
            case 1: //Mode "Play"
                previousState = 1;
                modeEtat = 1;
                jeu();
                choixMenu = 0;
                break;
            case 2://Mode "Help"
                previousState = 2;
                modeEtat = 2;
                Aide();
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
