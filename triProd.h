#ifndef TRIPROD_H_INCLUDED
#define TRIPROD_H_INCLUDED
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
car *trierProduits(car *liste);
void afficherListe(car* liste);
// fonction qui tri les voitures selon le choix saisi par l'utilisateur
void afficherListe(car* liste) {
    car* temp = liste;
    while (temp != NULL) {
        printf("ID: %s, Marque: %s, Prix de location: %.2f\n",
               temp->id, temp->marque, temp->prix_location);
        temp = temp->nxt;
        temp->nxt=NULL;
    }
}
car* trierProduits(car* liste) {
    FILE* f;
    char choice;
    car *temp, *p;
    int per;
    char pr[30];

    do {
        printf("                                          Veuillez choisir le critere de tri :\n");
        printf("                                          a. Par Marque\n");
        printf("                                          b. Par Prix de location\n\n");
        printf("                                          Faites entrer votre choix : ");
        scanf(" %c", &choice);

        f = fopen("Cars.csv", "r");
        if (f == NULL) {
            printf("Erreur lors de l'ouverture du fichier.\n");
            return liste; // Ou NULL selon la logique de votre programme
        }

        p = malloc(sizeof(car));
        while (fscanf(f, "%s\t %s\t %s\t %s\t %s\t %d\t %.2f\t %d",
                      p->id, p->marque, p->nom_utilisateur, p->modele,
                      p->type_carburant, &p->nb_places, &p->prix_location,
                      &p->status) == 8) {
            p->nxt = malloc(sizeof(car));
            p = p->nxt;
        }
        p->nxt = NULL;
        fclose(f);

        switch (choice) {
            case 'a':
                if (liste != NULL) {
                    for (temp = liste; temp->nxt != NULL; temp = temp->nxt) {
                        for (p = temp->nxt; p != NULL; p = p->nxt) {
                            if (strcmp(p->marque, temp->marque) < 0) {
                                strcpy(pr, p->marque);
                                strcpy(p->marque, temp->marque);
                                strcpy(temp->marque, pr);
                            }
                        }
                    }
                }
                printf("les marques triees :\n");
                afficherListe(liste);
                break;

            case 'b':
                if (liste != NULL) {
                    for (temp = liste; temp->nxt != NULL; temp = temp->nxt) {
                        for (p = temp->nxt; p != NULL; p = p->nxt) {
                            if (p->prix_location < temp->prix_location) {
                                per = p->prix_location;
                                p->prix_location = temp->prix_location;
                                temp->prix_location = per;
                            }
                        }
                    }
                }
                printf("les prix triees : \n");
                afficherListe(liste);
                break;

            default:
                printf("Votre choix est invalide !!\n");
        }

    } while (choice < 'a' || choice > 'b');

    return liste;
}

#endif // TRIPROD_H_INCLUDED
