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
    while (ModeEtat == 1)
    {
        printf("Pressez 5 pour quitter:");
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
