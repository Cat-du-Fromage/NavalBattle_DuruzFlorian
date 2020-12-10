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



    while (modeEtat == 2 && quitAide != 'q')
    {
        printf("\nPressez <q> pour quitter:");
        scanf("%c", &quitAide);
        if (quitAide == 'q')
        {
            modeEtat = 0;
        }
        /*
        else if (quitAide == 0)
        {
            emptyBuffer();
        }
         */
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
 * @brief initGameGrid - Return if the shot land on a ship or not
 * @param Ligne - Line of the game Grid
 * @param Colonne - Row of the Game Grid
 * @param shotLigne - Ligne selected by the player
 * @param shotColonne - Row Selected by the player
 * @return bool - true if a ship is hit
 */
//=====================================================================================================

/*
bool initGameGrid(int optionVerification ,int Ligne, int Colonne, int shotLigne, int shotColonne, ...)
{
    //Init Ship Grid
    char ShipGrid[Ligne][Colonne];
        A  B  C  D  E  F  G  H  I  J
     *
     * 1   p  p  p  p  p  -  -  -  -  -
     * 2   -  -  -  -  -  -  -  -  -  -
     * 3   -  -  -  -  -  -  -  c  -  -
     * 4   -  -  -  s  s  s  -  c  -  -
     * 5   -  -  -  -  -  -  -  c  -  -
     * 6   -  s  -  -  -  -  -  c  -  -
     * 7   -  s  -  -  -  -  -  -  -  -
     * 8   -  s  -  -  -  t  -  -  -  -
     * 9   -  -  -  -  -  t  -  -  -  -
     * 10  -  -  -  -  -  -  -  -  -  -


    //Porte avion
    char pShip = "p";
    ShipGrid[1][1] = pShip;
    ShipGrid[1][2] = pShip;
    ShipGrid[1][3] = pShip;
    ShipGrid[1][4] = pShip;
    ShipGrid[1][5] = pShip;

    char cShip = "c";

    if (optionVerification == 1)
    {
        for (int i = 0; i < Ligne; ++i)
        {
            for (int j = 0; j < Colonne; ++j)
            {
                if (ShipGrid[shotLigne][shotColonne] == pShip)
                {
                    printf("\nHit!\n");
                    return true;
                }
                else
                {
                    printf("\nMiss!\n");
                    return false;
                }
            }
        }
    }



}
*/

//=====================================================================================================
/**
 * @brief jeu - "Main" play function,
 * @return void
 */
//=====================================================================================================
void jeu()
{
    bool QuitGame = false;

    //DIMENSION DE LA GRILLE
    //ligne
    int ligne = 11;
    //COLONNE
    int colonne = 11;

    char Alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    char choiceAlpha = "z";
    int choiceNum = 0;
    //Player Grid View
    int grid[ligne][colonne];

    //=================================================================
    //Init Ship Grid
    char ShipGrid[ligne][colonne];
/*
        A  B  C  D  E  F  G  H  I  J
*
*   1   p  p  p  p  p  -  -  -  -  -
*   2   -  -  -  -  -  -  -  -  -  -
*   3   -  -  -  -  -  -  -  c  -  -
*   4   -  -  -  s  s  s  -  c  -  -
*   5   -  -  -  -  -  -  -  c  -  -
*   6   -  s  -  -  -  -  -  c  -  -
*   7   -  s  -  -  -  -  -  -  -  -
*   8   -  s  -  -  -  t  -  -  -  -
*   9   -  -  -  -  -  t  -  -  -  -
*   10  -  -  -  -  -  -  -  -  -  -
    */
    int pShip = 1;
    ShipGrid[1][1] = pShip;
    ShipGrid[1][2] = pShip;
    ShipGrid[1][3] = pShip;
    ShipGrid[1][4] = pShip;
    ShipGrid[1][5] = pShip;

    int cShip = 2;
    ShipGrid[3][8] = cShip;
    ShipGrid[4][8] = cShip;
    ShipGrid[5][8] = cShip;

    for (int i = 0; i < ligne; ++i)
    {
        for (int j = 0; j < colonne; ++j)
        {
            if (ShipGrid[i][j] != pShip && ShipGrid[i][j] != cShip)
            {
                ShipGrid[i][j] = 0;
            }
        }
    }
    //=================================================================

    for(int a=0; a < ligne; a++)
    {
        for(int b=0; b < colonne; b++)
        {
            //grid[a][b] = i++;
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
    printf("\nPressez 5 pour quitter:\n");
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
        int i = 0;

        /*================================================
         *
         * Display the game grid
         * Display the selector controler part of the grid (A-Z; 1-15)
         *
         ================================================*/

        scanf("%c%d", &choiceAlpha, &choiceNum);
        if (choiceAlpha == 'q')
        {
            modeEtat = 0;
        }

        if(choiceNum > 0 && choiceNum < 11)
        {
            if (choiceAlpha != "z" && choiceNum != 0)
            {
                for (int j = 0; j < ligne; ++j)
                {
                    int shotLigne = 0;
                    if (Alphabet[j] == choiceAlpha)
                    {
                        shotLigne = j;
                        if (ShipGrid[j][choiceNum] != 0)
                        //if (initGameGrid(1, ligne, colonne, shotLigne, choiceNum) == true)
                        {
                            printf("\n%d\n", ShipGrid[shotLigne][choiceNum]);
                            grid[j][choiceNum] = 4;
                            if (grid[1][1] == 4 && grid[1][2] == 4 && grid[1][3] == 4 && grid[1][4] == 4 && grid[1][5] == 4)
                            {
                                grid[1][1] = 5;
                                grid[1][2] = 5;
                                grid[1][3] = 5;
                                grid[1][4] = 5;
                                grid[1][5] = 5;
                            }

                            else if (grid[3][8] == 4 && grid[4][8] == 4 && grid[5][8] == 4)
                            {
                                grid[3][8] = 5;
                                grid[4][8] = 5;
                                grid[5][8] = 5;
                            }



                            //Search for the line corresponding to the letter choose by the player
                            updateGrid(ligne, colonne, grid);
                            printf("\nChoisissez la case a abattre:");
                            printf("\nPressez 5 pour quitter:\n");
                            putchar('\n');

                        }
                        else
                        {
                            printf("\nMiss!");
                        }
                    }
                }
            }
            else
            {
                printf("\nCase impossible SALE MERDE!:\n");
                printf("\nChoisissez la case a abattre:\n");
                printf("\nPressez 5 pour quitter:\n");
            }
        }
        //scanf("%d", &QuitGame);

        //Return to main menu
        /*
        if (QuitGame == true)
        {
            modeEtat = 0;
        }
         */
    }
}

//=====================================================================================================
/**
 * @brief main - Main menu, State machine system
 * @return void
 */
//=====================================================================================================
void main()
{
    setbuf(stdout,0);
    /*===========================

    * State Machine
    * States:
    * 0/Default : Main Menu - function main()
    * 1         : Play - function jeu()
    * 2         : Help menu - function Aide()

    ===========================*/
    int choixMenu = 0;

    while (modeEtat == 0 && choixMenu == 0)
    {
        choixMenu = 0;
        printf("\nBienvenu dans La bataille Navale");
        printf("\n1 : JOUER");
        printf("\n2 : AIDE DU JEU");
        printf("\n5 : QUITTER");
        printf("\nChoisissez le mode voulu parmis en entrant le chiffre correspondant ci-dessus.");
        printf("\nVotre Choix:");
        int res = scanf("%d", &choixMenu);
        if (res == 0)
        {
            emptyBuffer();
        }
        //scanf("%d", &choixMenu);
        switch (choixMenu)
        {
            case 0:
                modeEtat = 0;
                choixMenu = 0;
                break;
            case 1: //Mode "Play"
                modeEtat = 1;
                jeu();
                choixMenu = 0;
                break;
            case 2://Mode "Help"
                modeEtat = 2;
                Aide();
                choixMenu = 0;
                break;
            default:// mode "Main Menu
                modeEtat = 0;
                choixMenu = 0;
                break;
        }

    }

}
