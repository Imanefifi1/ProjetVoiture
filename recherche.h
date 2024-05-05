#ifndef RECHERCHE_H_INCLUDED
#define RECHERCHE_H_INCLUDED
typedef struct car {
    char id[30];
    char marque[30];
    char nom_utilisateur[30];
    char modele[30];
    char type_carburant[30];
    int nb_places;
    float prix_location;
    int status;
    struct car *nxt;
} car;
car *Research(car *liste, const char m[30], int dispo);
car *Research(car *liste, const char m[30], int dispo) {
    FILE *f;
    car *p = NULL; // Pointeur temporaire pour parcourir la liste
    car *v; // Pointeur pour cr�er de nouveaux �l�ments de la liste
    int r = 0;

    printf("\n============================================ Recherche des voitures ============================================\n\n");

    f = fopen("Cars.csv", "r");
    if (f == NULL) {
        printf("Probleme d'acces au fichier !!\n");
        exit(1);
    }

    while (1) {
        v = malloc(sizeof(car)); // Allouer de la m�moire pour une nouvelle voiture
        if (v == NULL) {
            printf("Erreur d'allocation de memoire.\n");
            exit(1);
        }

        int res = fscanf(f, " %s %s %s %s %s %d %f %d\n", v->id, v->marque, v->nom_utilisateur, v->modele, v->type_carburant, &v->nb_places, &v->prix_location, &v->status);
        if (res == EOF) {
            free(v); // Lib�rer la m�moire allou�e pour la derni�re voiture
            break; // Fin de fichier
        }

        if ((strcmp(v->marque, m) == 0) && (dispo == v->status)) {
            r++;
            printf("Voiture trouvee : %s %s %s %s %s %d %f %d\n", v->id, v->marque, v->nom_utilisateur, v->modele, v->type_carburant, v->nb_places, v->prix_location, v->status);

            // Ajouter la voiture � la liste
           v->nxt = NULL; // Initialiser le prochain pointeur � NULL

            if (liste == NULL) {
                liste = v; // Premier n�ud dans la liste
            }
			 else {
                p->nxt = v; // Ajouter le nouveau n�ud � la fin de la liste
            }
            p = v; // Mettre � jour le n�ud de parcours
        } else {
            free(v); // Lib�rer la m�moire allou�e pour la voiture non s�lectionn�e
        }
    }

    fclose(f);

    printf("Il se trouve %d voitures qui repondent a vos criteres.\n\n", r);
    if (r == 0) {
        printf("Aucune voiture trouvee !\n\n");
    }

    return liste; // Retourne la liste compl�te
}


#endif // RECHERCHE_H_INCLUDED
