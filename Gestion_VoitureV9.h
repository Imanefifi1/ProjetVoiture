#ifndef GESTION_VOITURE_H_INCLUDED
#define GESTION_VOITURE_H_INCLUDED


// Structure de données pour une voiture
typedef struct Voiture {
    char ID[50];                // Identifiant de la voiture
    char Marque[50];            // Marque de la voiture
    char NomUtilisateur[50];    // Nom de l'utilisateur de la voiture
    char Modele[50];            // Modèle de la voiture
    char TypeCarburant[20];     // Type de carburant utilisé par la voiture
    int NbPlaces;               // Nombre de places dans la voiture
    char Transmission[20];      // Type de transmission de la voiture
    float PrixLocation;         // Prix de location de la voiture
    char Disponibilite[20];     // Disponibilité de la voiture (Oui/Non)
    char Encredit[20];          // Statut de la voiture (En crédit ou non)
    int Nb_loc;                 // Nombre de locations de la voiture
    struct Voiture *suivant;    // Pointeur vers la voiture suivante dans la liste
} Voiture;


Voiture *Ajout_voiture(Voiture *liste, Voiture *nov_voit)
{
    Voiture *e, *p;
    // Allocation de la memoire pour une nouvelle voiture
    e = (Voiture *)malloc(sizeof(Voiture));

    // Copie des données de la nouvelle voiture dans la nouvelle allocation mémoire
    // (Cela peut être omis si les données sont déjà copiées dans nov_voit)
           e=nov_voit;
    // Vérification si la liste est vide
    if (liste == NULL) {
        e->suivant = liste;  // Le champ 'suivant' de la nouvelle voiture pointe vers NULL
        liste = e;           // La liste pointe maintenant vers la nouvelle voiture
    } else {
        // Si la liste n'est pas vide, on recherche le dernier maillon
        p = liste;
        while (p->suivant != NULL) {
            p = p->suivant;
        }
        // On ajoute la nouvelle voiture à la fin de la liste
        e->suivant = NULL;   // Le champ 'suivant' de la nouvelle voiture pointe vers NULL
        p->suivant = e;      // Le dernier maillon pointe vers la nouvelle voiture
    }
    // La fonction retourne la liste mise à jour
    return liste;
}
// Cette fonction ajoute une voiture à la liste des voitures avec des données spécifiques
Voiture *Ajout_liste_voiture(Voiture *liste, char **ut) {
    Voiture *e, *p; // Déclaration de deux pointeurs de type Voiture

    // Allocation de la mémoire pour une nouvelle voiture
    e = (Voiture *)malloc(sizeof(Voiture));

    // Lecture des données de la nouvelle voiture
    strcpy(e->ID, ut[0]);
    strcpy(e->Marque, ut[1]);
    strcpy(e->NomUtilisateur, ut[2]);
    strcpy(e->Modele, ut[3]);
    strcpy(e->TypeCarburant, ut[4]);
    e->NbPlaces = (int)atof(ut[5]);
    strcpy(e->Transmission, ut[6]);
    e->PrixLocation = (float) atof(ut[7]);
    strcpy(e->Disponibilite, ut[8]);
    strcpy(e->Encredit, ut[9]);
    e->Nb_loc = (int)atof(ut[10]);

    // Vérification si la liste est vide
    if (liste == NULL) {
        e->suivant = liste;
        liste = e;
    } else {
        // Recherche du dernier maillon
        p = liste;
        while (p->suivant != NULL) {
            p = p->suivant;
        }
        e->suivant = NULL;
        p->suivant = e;
    }
    return liste;
}

//Cet fonction permet de supprimer une voiture selon l'ID
Voiture* supprimer_voiture_ID(Voiture* liste, char *code)
 {
   Voiture* voitureCourante = liste;
    Voiture* voiturePrecedente = NULL;

    // Cas où la voiture à supprimer est en tête de liste
    if (voitureCourante != NULL && strcmp(voitureCourante->ID , code)==0) {
        liste = voitureCourante->suivant;
        free(voitureCourante);
        return;
    }

    // Parcours de la liste pour trouver la voiture à supprimer
    while (voitureCourante != NULL && strcmp(voitureCourante->ID, code)!=0) {
        voiturePrecedente = voitureCourante;
        voitureCourante = voitureCourante->suivant;
    }

    // Cas où la voiture à supprimer est en milieu ou en fin de liste
    if (voitureCourante == NULL) {
        printf("La voiture avec le code %d n'a pas ete trouvee.\n", code);
        return voitureCourante;
    }

    voiturePrecedente->suivant = voitureCourante->suivant;
    free(voitureCourante);
    return liste ;

 }

// Cette fonction charge les données des voitures à partir d'un fichier CSV et les ajoute à la liste des voitures
Voiture * charger_voitures(Voiture * lst_voit) {
    FILE *fic;
    char ligne[1000];
    char *ptr_chaine;

    // Ouverture du fichier CSV contenant les données des voitures
    fic = fopen("Liste_Voiture.csv", "rt");
    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    // Lecture du fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fic) != NULL) {
        // Suppression du retour chariot ou de la nouvelle ligne
        ligne[strcspn(ligne, "\r\n")] = '\0';

        // Extraction des données de la ligne
        ptr_chaine = strtok(ligne, ";");
        char *strut[11];  // Tableau pour stocker les éléments
        int j = 0;
        while (ptr_chaine != NULL) {
            strut[j++] = ptr_chaine;
            ptr_chaine = strtok(NULL, ";");
        }

        // Ajout de la voiture à la liste
        lst_voit = Ajout_liste_voiture(lst_voit, strut);
    }
    fclose(fic);
    return lst_voit;
}

// Cette fonction modifie les informations d'une voiture en utilisant son ID
void *Modifier_voiture(Voiture *liste,char *IDmodifier,float PrixLocation,char *Disponibilite) {
    Voiture *p = liste;
    int IDtrouvee = 0;

    // Recherche de la voiture à modifier en utilisant son ID
    while (p != NULL) {
        if (strcmp(p->ID, IDmodifier) == 0) {
            // Modification des informations de la voiture si elles sont spécifiées
            if (PrixLocation != -1) p->PrixLocation = PrixLocation;
            if (strcmp(Disponibilite, "") != 0) strcpy(p->Disponibilite, Disponibilite);
            printf("modification effectuee avec succes...\n");
            IDtrouvee = 1;
            break;
        }
        p = p->suivant;
    }
}

// Cette fonction cherche une voiture dans la liste en utilisant son ID
int chercher_voiture(Voiture *liste, char *ID) {
    Voiture *p = liste;
    int IDtrouvee = 0;

    // Recherche de la voiture en utilisant son ID
    while (p != NULL) {
        if (strcmp(p->ID, ID) == 0) {
            IDtrouvee = 1;
            break;
        }
        p = p->suivant;
    }
    return IDtrouvee;
}

// Cette fonction trie les voitures dans la liste en fonction du nombre de locations
void Trier_voiture(Voiture *liste)
{
    Voiture* tmp,*p;
    char PR[20];
    float prf ;
    int prentier ;
// Vérification si la liste n'est pas vide
    if(liste!=NULL)
    {
        // Parcours de la liste pour trier les voitures en fonction du nombre de locations
        for(tmp=liste;tmp->suivant!=NULL;tmp=tmp->suivant)
        {
            for(p=tmp->suivant;p!=NULL ;p=p->suivant)
            {
                if(p->Nb_loc>tmp->Nb_loc)
                {
                    // Échange des informations des voitures si nécessaire
                    strcpy(PR,p->Disponibilite);
                    strcpy(p->Disponibilite,tmp->Disponibilite);
                    strcpy(tmp->Disponibilite,PR);

                    strcpy(PR,p->Encredit);
                    strcpy(p->Encredit,tmp->Encredit);
                    strcpy(tmp->Encredit,PR);

                    strcpy(PR,p->ID);
                    strcpy(p->ID,tmp->ID);
                    strcpy(tmp->ID,PR);

                    strcpy(PR,p->Marque);
                    strcpy(p->Marque,tmp->Marque);
                    strcpy(tmp->Marque,PR);

                    strcpy(PR,p->Modele);
                    strcpy(p->Modele,tmp->Modele);
                    strcpy(tmp->Modele,PR);

                    strcpy(PR,p->NomUtilisateur);
                    strcpy(p->NomUtilisateur,tmp->NomUtilisateur);
                    strcpy(tmp->NomUtilisateur,PR);

                    strcpy(PR,p->Transmission);
                    strcpy(p->Transmission,tmp->Transmission);
                    strcpy(tmp->Transmission,PR);

                    strcpy(PR,p->TypeCarburant);
                    strcpy(p->TypeCarburant,tmp->TypeCarburant);
                    strcpy(tmp->TypeCarburant,PR);

                    prentier=p->NbPlaces;
                    p->NbPlaces=tmp->NbPlaces;
                    tmp->NbPlaces=prentier;


                    prf=p->PrixLocation;
                    p->PrixLocation=tmp->PrixLocation;
                    tmp->PrixLocation=prf;

                    prentier=p->Nb_loc;
                    p->Nb_loc=tmp->Nb_loc;
                    tmp->Nb_loc=prentier;

                }

            }
        }

    }
// Affichage de la liste triée
    Afficher_voit(liste);
}

// Cette fonction met à jour le fichier CSV avec les données actuelles des voitures
Voiture * Miseajour_fic_voiture(Voiture *list_voit) {
    Voiture *p = list_voit;
    FILE *fic = fopen("Liste_Voiture.csv", "w");

    // Ouverture du fichier CSV pour écriture
    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    // Parcours de la liste pour écrire les données des voitures dans le fichier
    while(p != NULL) {
        fprintf(fic, "%s;%s;%s;%s;%s;%d;%s;%.2f;%s;%s;%d\n", p->ID, p->Marque,
                p->NomUtilisateur, p->Modele, p->TypeCarburant,
                p->NbPlaces, p->Transmission, p->PrixLocation,
                p->Disponibilite, p->Encredit, p->Nb_loc);
        p = p->suivant ;
    }

    fclose(fic);
}

// Cette fonction affiche les informations des voitures ainsi que leur chiffre d'affaires
void Chiffre_aff(Voiture *liste) {
    Voiture *p = liste;
    float Ch_aff;

    // Affichage de l'en-tête du tableau
    printf("%-10s | %-15s | %-15s | %-12s | %-9s | %-10s | %-12s| %-10s\n", "ID", "Marque", "Modele", "Carburant", "N. Places", "P. Loc", "Disponibilite", "Chiffre d'affaire");
    printf("====================================================================================================================================================================\n");

    // Parcours de la liste pour afficher les informations de chaque voiture et leur chiffre d'affaires
    while (p != NULL) {
        Ch_aff = p->PrixLocation * p->Nb_loc;
        printf("%-10s | %-15s | %-15s | %-12s | %-9d| %-10.2f | %-12s| %-10.2f\n",
               p->ID, p->Marque, p->Modele, p->TypeCarburant, p->NbPlaces, p->PrixLocation, p->Disponibilite, Ch_aff);
        p = p->suivant;
    }
}

// Cette fonction affiche les informations des voitures disponibles
void Afficher_voit_dispo(Voiture *liste) {
    Voiture *p = liste;

    // Affichage de l'en-tête du tableau
    printf("%-10s | %-15s | %-20s | %-15s | %-12s | %-9s | %-15s | %-10s\n", "ID", "Marque", "Nom d'utilisateur", "Modele", "Carburant", "N. Places", "Transmission", "P. Loc");
    printf("==================================================================================================================================================================\n");

    // Parcours de la liste pour afficher les informations des voitures disponibles
    while (p != NULL) {
        if (strcmp(p->Disponibilite, "Oui") == 0) {
            printf("%-10s | %-15s | %-20s | %-15s | %-12s | %-9d | %-15s | %-10.2f\n",
                   p->ID, p->Marque, p->NomUtilisateur, p->Modele, p->TypeCarburant, p->NbPlaces,
                   p->Transmission, p->PrixLocation);
        }
        p = p->suivant;
    }
}

// Fonction pour afficher les informations des voitures dans la liste
void Afficher_voit(Voiture *liste) {
    Voiture *p = liste; // Pointeur vers le début de la liste
    // Affichage de l'en-tête du tableau des informations des voitures
    printf("%-10s | %-15s | %-25s | %-12s | %-10s | %-9s | %-10s | %-10s | %-12s| %-12s\n",
           "ID", "Marque", "Nom d'utilisateur", "Modele", "Carburant", "N. Places",
           "Transmission", "P. Loc", "Disponibilite", "Nombre Location");
    printf("=====================================================================================================================================================================================================================================\n");
    // Parcours de la liste pour afficher les informations de chaque voiture
    while (p != NULL) {
        // Affichage des informations d'une voiture
        printf("%-10s | %-15s | %-30s | %-12s | %-10s | %-9d | %-10s | %-10.2f | %-12s| %-10d\n",
               p->ID, p->Marque, p->NomUtilisateur, p->Modele, p->TypeCarburant, p->NbPlaces,
               p->Transmission, p->PrixLocation, p->Disponibilite, p->Nb_loc);
        p = p->suivant; // Passage à la voiture suivante dans la liste
    }
}

// Cette fonction permet de louer une voiture en utilisant son ID
void *louer_voiture(Voiture *liste, char *ID) {
    Voiture *p = liste;
    int IDtrouvee = 0;

    // Recherche de la voiture à louer en utilisant son ID
    while (p != NULL) {
        if (strcmp(p->ID, ID) == 0 &&  strcmp(p->Disponibilite,"Oui")==0) {
            // Incrémentation du nombre de locations et mise à jour de la disponibilité de la voiture
            p->Nb_loc = p->Nb_loc + 1;
            strcpy(p->Disponibilite, "Non");
            printf("Voiture louer avec succès\n");
            IDtrouvee = 1;
            break;
        }
        p = p->suivant;
    }
    // Affichage si la voiture n'est pas disponible
    if (IDtrouvee == 0) printf("Voiture non disponible\n");
    return p;
}





#endif // GESTION_VOITURE_H_INCLUDED
