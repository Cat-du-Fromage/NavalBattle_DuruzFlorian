#include <stdio.h>
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

/*=============================

 * "JOUER"
 * Jeu de la bataille navale

 ============================*/
void jeu()
{
    int QuitGame = 0;

    //DIMENSION DE LA GRILLE

    //COLONNE
    int Colonne = 10;
    //Ligne
    int Ligne = 15;

    char Alphabet[] = {'0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    int grid[Colonne][Ligne];

    //INITIALISER LE TABLEAU AVANT

    while (ModeEtat == 1)
    {
        /*================================
         * Affichage de la grille de Jeu
         * Affichage de des zones de Contrôle (A-Z; 1-15)
         *
         ================================*/
        for (int i = 0; i <= Colonne ; ++i)
        {
            for (int j = 0; j <= Ligne+1; ++j)
            {
                if (i == 0 && j == 0)
                {

                }
                else if (i == 0)
                {

                    printf("%d", j);

                }
                else if (j == 0)
                {
                    //printf("%d", i);
                    printf("%3c", Alphabet[i]);
                }
            }
        }



        printf("\nPressez 5 pour quitter:");
        scanf("%d", &QuitGame);
        if (QuitGame == 5)
        {
            ModeEtat = 0;
        }
    }
}





/*=============================

 * "Menu Principal"
 * Affiche Les différents choix possibles
 * Jouer
 * Aide du jeu

 ============================*/


void main()
{
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
