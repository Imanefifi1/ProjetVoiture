#ifndef GESTION_UTILISATEUR_H_INCLUDED
#define GESTION_UTILISATEUR_H_INCLUDED

typedef struct Utilisateur {
    char ID[50];
    char nom[50];
    char type[50];
    char PW[50];
    struct Utilisateur *suivant;
} Utilisateur;
Utilisateur *Ajout_Liste_utilisateur(Utilisateur *tete, char **ut) {
    Utilisateur *e, *p;
    // Allocation de la memoire
    e = (Utilisateur *)malloc(sizeof(Utilisateur));
    // Lecture des donnÃ©️es
    strcpy(e->ID, ut[0]);
    strcpy(e->nom, ut[1]);
    strcpy(e->type, ut[2]);
    strcpy(e->PW, ut[3]);

    if (tete == NULL) {
        e->suivant = tete;
        tete = e;
    } else {
        // Recherche du dernier maillon
        p = tete;
        while (p->suivant != NULL) {
            p = p->suivant;
        }
        e->suivant = NULL;
        p->suivant = e;
    }
    return tete;
}

Utilisateur *Ajout_Utilisateur(Utilisateur *tete, Utilisateur *nov_Util)
{
   Utilisateur *e, *p;
    // Allocation de la memoire
    e = (Utilisateur*)malloc(sizeof(Utilisateur));
    // Lecture des donnees
    if (tete == NULL) {
        e->suivant = tete;
        tete = e;
    } else {
        // Recherche du dernier maillon
        p = tete;
        while (p->suivant != NULL) {
            p = p->suivant;
        }
        e->suivant = NULL;
        p->suivant = e;
    }
    return tete;

}
Utilisateur *  charger_utilisateurs(Utilisateur * lst_util )
{
    FILE *fic;
    char ligne[100];
    char *ptr_chaine;
        fic = fopen("utilisateur.csv", "rt");

    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    while (fgets(ligne, sizeof(ligne), fic) != NULL) {
        ligne[strcspn(ligne, "\r\n")] = '\0';  // Supprime le retour chariot ou la nouvelle ligne
        ptr_chaine = strtok(ligne, ";");
        char *strut[4];  // Vous avez besoin d'un tableau pour stocker les Ã©️lÃ©️ments
        int j = 0;
        while (ptr_chaine != NULL) {
            strut[j++] = ptr_chaine;
            ptr_chaine = strtok(NULL, ";");
        }
        lst_util = Ajout_Liste_utilisateur(lst_util,strut);
    }
    close(fic);
    return lst_util ;

    }




//Cet fonction permet de supprimer un utilisateur selon l'ID
Utilisateur* supprimer_Utilisateur_ID(Utilisateur* liste, char *code)
 {
   Utilisateur* utilisateurCourante = liste;
   Utilisateur* utilisateurPrecedente = NULL;

    // Cas où l'utilisateur à supprimer est en tête de liste
    if (utilisateurCourante != NULL && strcmp(utilisateurCourante->ID , code)==0) {
        liste =utilisateurCourante->suivant;
        free(utilisateurCourante);
        return;
    }

    // Parcours de la liste pour trouver l'utilisateur à supprimer
    while (utilisateurCourante != NULL && strcmp(utilisateurCourante->ID, code)!=0) {
        utilisateurPrecedente = utilisateurCourante;
       utilisateurCourante = utilisateurCourante->suivant;
    }

    // Cas où l'utilisateur à supprimer est en milieu ou en fin de liste
    if (utilisateurCourante == NULL) {
        printf("L'utilisateur avec le code %d n'a pas ete trouvee.\n", code);
        return utilisateurCourante;
    }

    utilisateurPrecedente->suivant = utilisateurCourante->suivant;
    free(utilisateurCourante);
    return liste ;

 }

Utilisateur* Miseajour_fic_Utilisateur(Utilisateur *list_util)
{
	 Utilisateur *p = list_util;
     FILE *fic = fopen("utilisateur.csv", "w");

    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
while(p!=NULL)
{
    fprintf(fic, "%s;%s;%s;%s\n", p->ID, p->nom,p->type, p->PW);
    p=p->suivant ;
}

    fclose(fic);


}


#endif // GESTION_UTILISATEUR_H_INCLUDED
