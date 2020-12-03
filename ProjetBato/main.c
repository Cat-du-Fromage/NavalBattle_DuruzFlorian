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


int ModeEtat = 0;


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
    int QuitAide = 0;
    while (ModeEtat == 2)
    {
        printf("Pressez 5 pour quitter:");
        scanf("%d", &QuitAide);
        if (QuitAide == 5)
        {
            ModeEtat = 0;
        }
    }
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

    for (int i = 0; i <ligne ; ++i)
    {
        for (int j = 0; j <colonne; ++j)
        {

            if (grid[i][j] == 0)
            {
                printf(" ");

            }
            else if (grid[i][j] == 1)
            {
                printf("%3d", j);
                //printf("%3c", Alphabet[i]);

            }
            else if (grid[i][j] == 2)
            {
                printf("%c", Alphabet[i]);
                //printf("%d", j);

            }
            else if (grid[i][j] == 4)
            {
                char r = 'x';
                printf("%3c", r);

            }
            else
            {
                int e = 0;
                printf("%3d", e);
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

bool initGameGrid(int Ligne, int Colonne, int shotLigne, int shotColonne)
{
    //Init Ship Grid
    char ShipGrid[Ligne][Colonne];

    //Porte avion
    char PShip = "p";
    ShipGrid[1][1] = PShip;
    ShipGrid[1][2] = PShip;
    ShipGrid[1][3] = PShip;
    ShipGrid[1][4] = PShip;
    ShipGrid[1][5] = PShip;


    //placement des batos en dur pour la version 0.1
    for (int i = 0; i < Ligne; ++i)
    {
        for (int j = 0; j < Colonne; ++j)
        {
            if (ShipGrid[shotLigne][shotColonne] == PShip)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
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

    //DIMENSION DE LA GRILLE
    //Ligne
    int Ligne = 10;
    //COLONNE
    int Colonne = 10;

    char Alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    char choiceAlpha = "z";
    int choiceNum = 0;
    //Player Grid View
    int grid[Ligne][Colonne];

    for(int a=0;a<Ligne;a++)
    {
        for(int b=0;b<Colonne;b++)
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

    while (ModeEtat == 1)
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
        for (int i = 0; i <Ligne ; ++i)
        {
            for (int j = 0; j <Colonne; ++j)
            {

                if (grid[i][j] == 0)
                {
                    printf(" ");

                }
                else if (grid[i][j] == 1)
                {
                    printf("%3d", j);
                    //printf("%3c", Alphabet[i]);

                }
                else if (grid[i][j] == 2)
                {
                    printf("%c", Alphabet[i]);
                    //printf("%d", j);

                }
                else if (grid[i][j] == 4)
                {
                    char r = "x";
                    printf("%3c", r);
                    //printf("%d", j);

                }
                else
                {
                    int e = 0;
                    printf("%3d", e);
                }
            }
            putchar('\n');
        }

        //printf("\nChoisissez la case a abattre:");
        scanf("%c%d", &choiceAlpha, &choiceNum);
        if (choiceAlpha != "z" && choiceNum != 0)
        {
            for (int j = 0; j < Ligne; ++j)
            {
                int shotligne = 0;
                if (Alphabet[j] == choiceAlpha)
                {
                    shotligne = j;
                    if (initGameGrid(Ligne, Colonne, shotligne, choiceNum) == true)
                    {
                        printf("\nTOUCHE!\n");
                        //Search for the line corresponding to the letter choose by the player
                        grid[j][choiceNum] = 4;
                        updateGrid(Ligne, Colonne, grid);

                    }
                    else
                    {
                        printf("\nRATE!");
                    }
                }
            }
        }
        printf("\nChoisissez la case a abattre:");
        printf("\nPressez 5 pour quitter:");
        putchar('\n');
        scanf("%d", &QuitGame);
        if (QuitGame == true)
        {
            ModeEtat = 0;
        }
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
    printf("Hello, World!\n");
    /*===========================

    * Machine d'états
    * Switch case pour la navigation entre les différents modes
    * 0/Default : On entre dans le Mode "Menu Principal"; voir fonction MenuPrincipal()
    * 1         : On entre dans le Mode "Jouer"; voir fonction Jeu()
    * 2         : Mode "Aide de Jeu"; voir fonction Aide()

    ===========================*/

    int ChoixMenu = 0;

    while (ModeEtat == 0)
    {
        printf("\nBienvenu dans La bataille Navale");
        printf("\n1 : JOUER");
        printf("\n2 : AIDE DU JEU");
        printf("\n5 : QUITTER");
        printf("\nChoisissez le mode voulu parmis en entrant le chiffre correspondant ci-dessus.");
        printf("\nVotre Choix:");
        scanf("%d", &ChoixMenu);

        switch (ChoixMenu)
        {
            case 0:
            ModeEtat = 0;
            break;
            case 1: //Mode "Play"
            ModeEtat = 1;
            jeu();
            break;
            case 2://Mode "Help"
            ModeEtat = 2;
            Aide();
            break;
            default:// mode "Main Menu
            ModeEtat = 0;
            break;
        }


    }

}
