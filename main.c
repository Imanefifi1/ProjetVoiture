#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include<time.h>
#include "Ecran_AccV9.h"
#include "Gestion_VoitureV9.h"
#include "Gestion_LeasingV9.h"
#include "Gestion_UtilisateurV9.h"
#include "Gestion_PannesV9.h"
#include "Stocker.h"
#include "Somme.h"
#include "TriProd.h"
#include "recherche.h"



Utilisateur *getInput()
{
 int i;
 printf("\n");
    printf("***************Identification*****************\n");
    printf("Entrer le nom:");
    static Utilisateur u;
    fflush(stdin);
    fgets(u.nom,20,stdin);
    char *pos;
    pos=strchr(u.nom,'\n');
    if(pos!=NULL)
    {
       *pos='\0';
    }
    if(strcmp(u.nom,"0")==0)
    {
        printf("Identification arrêter\n");
        getch();
        return NULL;

    }
    printf("Entrer le mot de passe :");
    fflush(stdin);
    i=0;
//    textcolor(WHITE);
    for(;;)
    {
        u.PW[i]=getch();
        if(u.PW[i]==13)
        {
            break;
        }
        printf("*");
        i++;
    }
    u.PW[i]='\0';
     if(strcmp(u.PW,"0")==0)
    {
        printf("Identification arrêter\n");
        getch();
        return NULL;

    }
    getch();
    return &u;
}

int main() {
    Utilisateur *lst_util = NULL,*nouvelutil=NULL;
    Voiture *lst_voit=NULL,*nouvelvoit=NULL, *t=NULL;
    VoitureCredit *lstVoitCredit=NULL,*nouvelvoitCredit=NULL;
    VoiturePannes *lstVoiturePannes=NULL,*nouvelvoitPanne=NULL ;
    char nom[100], PW[100],Profil[20],ID[50],IDPann[50],IDutil[50];
     int NbPlaces,dispo;
     float PrixLocation,PrixPanne;
     char Disponibilite[50],IDmod[50],IDmodPann[50],IDV[50];
    int flag = 0;
    char line[100]; // Taille max de la ligne
    char *tok; // Pointeur vers un champ
    car *liste = malloc(sizeof(car));
    liste = NULL;
    FILE *fich, *f;
    char m[30],ch;
    float prix;

    ecran_acc() ;


    lst_util=charger_utilisateurs(lst_util);
    lst_voit=charger_voitures(lst_voit) ;
    lstVoitCredit=chargervoituresCredit(lstVoitCredit) ;
    lstVoiturePannes=chargervoituresPannes(lstVoiturePannes);
       printf("\033[0;31m");
       printf("\n");
    printf("\t\t\t************** Bienvenue %c l%capplication : VacayCar **************\n",133,39) ;
    printf("\n");
     printf("\033[0;00m");

  /**************************************/

   do
    {
        Utilisateur *u=getInput();



            Utilisateur *utilisa = lst_util;  // Commencez Ã  partir de la tÃªte de la liste
            while (utilisa != NULL)
            {
                if (strcmp(utilisa->nom, u->nom) == 0 && strcmp(utilisa->PW, u->PW) == 0)
                {
                    flag = 1;
                    strcpy(Profil,utilisa->type);
                    strcpy(nom,utilisa->nom);
                    break;
                }
                utilisa = utilisa->suivant;
            }
    }
    while (flag == 0);


  /*************************************/


int i,rep,rep1,rep2,rep3;

do
    {
        menu_principale://etiquette de go to
        printf("\n============== Menu Principal ==============\n");
        printf("1. Gestion des voitures \n");
        printf("2. Leasing \n");
        printf("3. Gestion des pannes\n");
        printf("4. La r%cparation\n",130);
        if(strcmp(Profil,"Super Admin")==0 )printf("5. Ajouter  un utilisateur\n");
        if(strcmp(Profil,"Super Admin")==0 )printf("6. Supprimer un utilisateur\n");
        printf("7. Quitter\n");
        printf("===============================================\n");
        printf("Choix : ");
        scanf("%d", &rep1);
        switch(rep1)
        {
        case 1 :
            do
            {
            printf("\n============== Menu Gestion des voitures ==============\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("1. Ajouter une voiture\n");
            printf("2. Afficher les voitures disponibles\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("3. Supprimer une voiture\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("4. Modifier une voiture\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("5. Recherche une voiture par marque et disponibilite\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("6. Trier des produitsn");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("7. Stocker des produits");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("8. Louer une voiture\n");
            printf("9. Voitures les plus louer\n");
            printf("10. Chiffre d%caffaire de location\n",39);
            printf("11. Retour au Menu principale\n");
            printf("=========================================================\n");
            printf("Choix : ");
            scanf("%d", &rep);
            switch(rep)
            {
            case 1 :
                    do
                      {

                        nouvelvoit=(Voiture*)malloc(sizeof(Voiture));
                        printf("ajouter une nouvelle voiture:\n");
                        printf("ID:");
                        scanf("%s",nouvelvoit->ID);
                        printf("\n");
                        printf("Marque:");
                        scanf("%s",nouvelvoit->Marque);
                        printf("\n");
                         printf("Modele:");
                        scanf("%s",nouvelvoit->Modele);
                        printf("\n");
                         printf("Carburant:");
                        scanf("%s",nouvelvoit->TypeCarburant);
                        printf("\n");
                         printf("Nbre de places:");
                        scanf("%d",&nouvelvoit->NbPlaces);
                        printf("\n");
                         printf("Transmission:");
                        scanf("%s",nouvelvoit->Transmission);
                        printf("\n");
                         printf("Prix/jr:",47);
                        scanf("%f",&nouvelvoit->PrixLocation);
                        printf("\n");
                        printf("Disponibilite:",130);
                        scanf("%s",nouvelvoit->Disponibilite);
                        printf("\n");
                        printf("En credit Oui/Non:");
                        scanf("%s",nouvelvoit->Encredit);
                        printf("\n");

                        strcpy(nouvelvoit->NomUtilisateur,nom);
                        nouvelvoit->Nb_loc=0 ;
                        lst_voit=Ajout_voiture(lst_voit,nouvelvoit);
                        /******************************/
                        if(strcmp(nouvelvoit->Encredit,"Oui")==0)
                        {
                             nouvelvoitCredit=(VoitureCredit*)malloc(sizeof(VoitureCredit));
                             strcpy(nouvelvoitCredit->ID,nouvelvoit->ID);
                             printf("Prix Achat:");
                             scanf("%f",&nouvelvoitCredit->PrixAchat);
                             printf("\n");
                             printf("Apport:");
                             scanf("%f",&nouvelvoitCredit->Apport);
                             printf("\n");
                             printf("Duree de credit:");
                             scanf("%d",&nouvelvoitCredit->Duree);
                             printf("\n");
                             printf("Date Achat:");
                             scanf("%d%d%d",&nouvelvoitCredit->DateAchat.jj,&nouvelvoitCredit->DateAchat.mm,&nouvelvoitCredit->DateAchat.aaaa);
                             printf("\n");
                             lstVoitCredit=AjoutvoitureCredit(lstVoitCredit,nouvelvoitCredit);
                             AffichervoitCredit(lstVoitCredit);
                        }
                        /******************************/

                        Afficher_voit(lst_voit);
                        printf("autres 1-oui/0-non\n");
                        scanf("%d",&i);
                    }while(i==1);
                        break;
            case 2 :

                    printf("\n====== Voitures Disponibles ======\n");
                    Afficher_voit_dispo(lst_voit);

                    break ;
            case 3 :

                      printf("Saisir ID de la voiture %c supprimer\n ",133);
                      scanf("%s",ID);
                      Voiture* liste =lst_voit ;
                      lst_voit=supprimer_voiture_ID(liste,&ID);
                       break;
            case 4:
                    printf("Donner ID pour modifier:\n");
                    scanf("%s",IDmod);
                    printf("Voulez-vous modifier le prix de locatio 1-oui/0-non:\n");
                    scanf("%d",&i);
                    if (i==0) PrixLocation=-1 ;
                    else{
                    printf("Entrer le nouveau prix:\n");
                    scanf("%f",&PrixLocation);
                    }
                    printf("Voulez-vous modifier la disponibilit%c 1-oui/0-non:\n",130);
                    scanf("%d",&i);
                    if (i==0) strcpy(Disponibilite,"") ;
                    else{
                    printf("Voiture disponible Oui/Non:\n");
                    scanf("%s",Disponibilite);
                    }

                    Modifier_voiture(lst_voit,&IDmod,PrixLocation,&Disponibilite);
                    break;
            case 5:
                Research(liste,m,dispo);
                break;
            case 6:
                trierProduits(liste);
                break;
            case 7:
                StockFile(f);
                afficherCSV(f);
                break;
            case 8:
                    //Afficher_voit(lst_voit);
                    do
                    {
                    printf("Donner le code de la voiture %c louer\n",133) ;
                    scanf("%s",IDmod);
                    if (chercher_voiture(lst_voit,IDmod) )
                    {

                        louer_voiture(lst_voit,IDmod);
                        break;
                    }
                    }while(!chercher_voiture(lst_voit,IDmod));
                    break;
            case 9:

                Trier_voiture(lst_voit);
                //Afficher_voit(lst_voit);
                break ;
            case 10 :

                Chiffre_aff(lst_voit);
                break ;

             case 11:goto menu_principale;
            default : printf("choix introuvable!");

            }
            }while(rep!=11);

        case 2 :
                do{

                   printf("\n============== Menu Leasing ==============\n");

                    printf("1. Liste de voitures %c cr%cdits \n",133,130);
                    if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("2. Le reste de cr%cdit\n",130);
                    printf("3. Cr%cdits qui sont termin%cs\n",130,130);
                    printf("4. Retour au menu principale\n");
                    printf("============================================\n");
                    printf("Choix : ");
                    scanf("%d", &rep2);
                    switch(rep2)
                    {
                        case 1:
                                  AffichervoitCredit(lstVoitCredit);
                            break;
                        case 2 :
                            ResteDeCredit(lst_voit,lstVoitCredit);
                            break ;
                        case 3 :
                            Credit_terminer(lstVoitCredit);
                            break ;
                case 4: goto menu_principale;
                break;
                    }
                        }while(rep2!=4);
        case 3 :
                        do
            {
            printf("\n============== Menu Gestion de pannes ==============\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("1. Saisir une panne d%cune voiture\n",39);
            printf("2. La liste des pannes\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("3. Pannes d%cune voiture\n",39);
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("4. Modifier une panne\n");
            if (strcmp(Profil,"Admin")==0 || strcmp(Profil,"Super Admin")==0 )printf("5. Supprimer une panne\n");
            printf("6. Retour au menu principale\n");
            printf("======================================================\n");
            printf("Choix : ");
            scanf("%d", &rep3);
            switch(rep3)
            {
            case 1 :

                 do
                      {

                        nouvelvoitPanne=(VoiturePannes*)malloc(sizeof(VoiturePannes));
                        printf("ajouter une nouvelle panne:\n");
                        do
                        {
                        printf("ID voiture:");
                        scanf("%s",IDmod);
                        if (chercher_voiture(lst_voit,IDmod) )
                        {
                           strcpy(nouvelvoitPanne->ID,IDmod);
                         break;
                        }
                        else printf("Voiture non trouv%ce, resaisir la voiture\n",130);
                        }while(!chercher_voiture(lst_voit,IDmod));
                        printf("\n");
                        do
                        {
                        printf("ID Panne:");
                        scanf("%s",IDmodPann);
                        if (chercher_panne(IDmodPann))
                        {
                           strcpy(nouvelvoitPanne->ID_Panne,IDmodPann);
                         break;
                        }
                        else printf("Panne non trouv%ce, resaisir la panne\n",130);
                        }while(!chercher_panne(IDmodPann));

                        printf("\n");
                        int deg ;
                        do
                            {
                                printf("Degr%ce endommag%ce:",130,130);
                                scanf("%d",&deg);

                            }while(deg<0 || deg>100) ;
                        nouvelvoitPanne->Degre_endmg=deg;
                        printf("\n");
                        printf("Prix de panne:");
                        scanf("%f",&nouvelvoitPanne->prix);
                        printf("\n");
                        lstVoiturePannes=Ajout_voiturePannes(lstVoiturePannes,nouvelvoitPanne);
                        printf("autres 1-oui/0-non\n");
                        scanf("%d",&i);
                    }while(i==1);
                        break;
                case 2:
                    liste_pannes() ;
                break;
                case 3 :

                    printf("Donner le code de la voiture\n") ;
                    scanf("%s",IDV);
                    Afficher_Panne_dispo(lstVoiturePannes,IDV);
                    break;
                case 4:
                    printf("Donner ID pour modifier:\n");
                    scanf("%s",IDmodPann);
                    printf("Voulez-vous modifier le prix de panne 1-oui/0-non:\n");
                    scanf("%d",&i);
                    if (i==0) PrixPanne=-1 ;
                    else{
                    printf("Entrer le nouveau prix:\n");
                    scanf("%f",&PrixPanne);
                    }

                   Modifier_voiture_Pannes(lstVoiturePannes,&IDmodPann,PrixPanne);
                    break;
                case 5:
                    printf("Saisir ID de Voiture %c supprimer\n ",133);
                      scanf("%s",IDV);
                       printf("Saisir ID de Panne %c supprimer\n ",133);
                      scanf("%s",IDPann);
                      VoiturePannes* liste =lstVoiturePannes;
                      lstVoiturePannes=supprimer_Panne_IDPannes(liste,&IDV,&IDPann);
                       break;
                case 6: goto menu_principale;
                break;
                    }
                }while(rep3!=6);
        case 4:
               printf("\n  ================================================ Historique de reparation de nos voitures : ================================================ \n \n");
            do{
                printf("                                               a. Les parties reparees de chaque voiture \n");
                printf("                                               b. Le degree d'endommagement de chaque voiture \n");
                printf("                                               c. Estimation du prix de reparation  \n");
                printf("                                               d. Les parties les plus endommagees de chaque voiture \n");
                printf("                                               e. Retour au menu principal \n");
                printf("                                                  Faites entrer votre choix : ");
                scanf(" %c", &ch);

			    switch (ch) {
                    case 'a':
                          // Ouvrir le fichier CSV en mode lecture
                            fich = fopen("RepV.csv", "rt"); // Utilisation du fichier "RepV.csv" comme chemin d'accès pour lire ses données
                            if (fich == NULL) {

                            printf("Erreur lors de l'ouverture du fichier.\n"); // Affichage d'un message d'erreur s'il y avait un problème d'accès au fichier

                            return ;

                             }

                             // Lire chaque ligne du fichier
                             while (fgets(line, sizeof(line), fich) != NULL) {
                             // Séparer la ligne en champs
                             tok = strtok(line, "   \t ");
                            while (tok != NULL) {
                             // Afficher chaque champ
                             printf(" %s  ", tok);
                             tok = strtok(NULL, "   \t ");
                               }
                             printf(" \n");
                               }

                             // Fermer le fichier
                              fclose(fich);
                        break;

                    case 'b':


                            // Ouvrir le fichier CSV en mode lecture
                            fich = fopen("degreedamages.csv", "rt"); // Utilisation du fichier "degreedamages.csv" comme chemin d'accès pour lire ses données
                            if (fich == NULL) {

                            printf("Erreur lors de l'ouverture du fichier.\n"); // Affichage d'un message d'erreur s'il y avait un problème d'accès au fichier

                            return ;

                             }

                             // Lire chaque ligne du fichier
                             while (fgets(line, sizeof(line), fich) != NULL) {
                             // Séparer la ligne en champs
                             tok = strtok(line, "   \t ");
                            while (tok != NULL) {
                             // Afficher chaque champ
                             printf(" %s  ", tok);
                             tok = strtok(NULL, "   \t ");
                               }
                             printf(" \n");
                               }

                             // Fermer le fichier
                              fclose(fich);
                        break;
                    case 'c':
                        SommeRep ( prix);
                        break;
                    case 'd':
                          // Ouvrir le fichier CSV en mode lecture
                            fich = fopen("PlusEndom.csv", "rt"); // Utilisation du fichier "PlusEndom.csv" comme chemin d'accès pour lire ses données
                            if (fich == NULL) {

                            printf("Erreur lors de l'ouverture du fichier.\n"); // Affichage d'un message d'erreur s'il y avait un problème d'accès au fichier

                            return ;

                             }

                             // Lire chaque ligne du fichier
                             while (fgets(line, sizeof(line), fich) != NULL) {
                             // Séparer la ligne en champs
                             tok = strtok(line, "   \t ");
                            while (tok != NULL) {
                             // Afficher chaque champ
                             printf(" %s  ", tok);
                             tok = strtok(NULL, "   \t ");
                               }
                             printf(" \n");
                               }

                             // Fermer le fichier
                              fclose(fich);
                        break;
                    case 'e':
                    	goto start ;
                    	break ;
                    default:
                        printf("Error !! \n \n");
                }
				} while(ch>'e' || ch<'z');

        case 5:

                        nouvelutil=(Utilisateur*)malloc(sizeof(Utilisateur));
                        printf("ajouter un nouvel utilisateur:\n");
                        printf("ID:");
                        scanf("%s",nouvelutil->ID);
                        printf("\n");
                        printf("Nom:");
                        scanf("%s",nouvelutil->nom);
                        printf("\n");
                         printf("Type:");
                        scanf("%s",nouvelutil->type);
                        printf("\n");
                         printf("PassWord:");
                        scanf("%s",nouvelutil->PW);
                        printf("\n");
      lst_util=Ajout_Utilisateur(lst_util,nouvelutil);
        goto menu_principale;

        break;

          case 6:
              printf("Saisir ID de l'utilisateur %c supprimer\n ",133);
                      scanf("%s",IDutil);
                      Utilisateur* liste =lst_util ;
                      lst_util=supprimer_Utilisateur_ID(liste,&IDutil);
                     goto menu_principale;
                     break;
        case 7 :

                break ;

                    }

    }while (rep1!=7);

       //*-----------------------666666666666666666------------------------
       lst_voit=Miseajour_fic_voiture(lst_voit);
       lstVoitCredit=Miseajour_fic_voiture_credit(lstVoitCredit);
       lstVoiturePannes=Miseajour_fic_voiture_Pannes(lstVoiturePannes);
       lst_util=Miseajour_fic_Utilisateur(lst_util);

        return 0;

}
