#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

int ModeEtat = 0;

/*=============================

 * "AIDE DU JEU"
 * Affiche l'aide du jeu

 ============================*/
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

/*=====================================================================================================

 * "JOUER"
 * Jeu de la bataille navale

 =======================================================================================================*/

void InitGameGrid(int Ligne, int Colonne)
{
    //Init Ship Grid
    char ShipGrid[Ligne][Colonne];

    //Mettre le lien avec Le fichier TXT ICI


    //placement des batos en dur pour la version 0.1
    for (int i = 0; i < Ligne; ++i)
    {
        for (int j = 0; j < Colonne; ++j)
        {

        }
    }
}


void jeu()
{
    bool QuitGame = false;

    //DIMENSION DE LA GRILLE
    //Ligne
    int Ligne = 11;
    //COLONNE
    int Colonne = 11;

    char Alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    //Player Grid View
    int grid[Ligne][Colonne];

    //Initiat ship palacement

    while (ModeEtat == 1)
    {

        /* Initialize the multidimensional array */
        //grid take a value according to the value of the vector
        //0 =top left of the grid
        //1 = A-z Value
        //2 = top number value
        //3 = Water Tile
        int i = 0;
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
        /*================================
         * Affichage de la grille de Jeu
         * Affichage de des zones de Contrôle (A-Z; 1-15)
         *
         ================================*/
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
                else
                {
                    int e = 0;
                    printf("%3d", e);
                }
            }
            putchar('\n');
        }

        printf("\nChoisissez la case à abattre:");

        printf("\nPressez 5 pour quitter:");
        scanf("%d", &QuitGame);
        if (QuitGame == true)
        {
            ModeEtat = 0;
        }
    }
}





/*=====================================================================================================

 * "Menu Principal"
 * Affiche Les différents choix possibles
 * Jouer
 * Aide du jeu

 =======================================================================================================*/


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
            case 1: //Mode "JOUER"
                ModeEtat = 1;
                jeu();
                break;
            case 2://Mode "AIDE DU JEU"
                ModeEtat = 2;
                Aide();
                break;
            default:
                ModeEtat = 0;
                break;
        }


    }

}
