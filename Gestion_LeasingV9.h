#ifndef GESTION_LEASING_H_INCLUDED
#define GESTION_LEASING_H_INCLUDED

typedef struct
{
    int jj;
    int mm;
    int aaaa;
    }Date;

typedef struct VoitureCredit
{
    char ID[50];
    float PrixAchat;
    float Apport;
    int Duree;
    Date DateAchat;
    struct VoitureCredit* suivant;
} VoitureCredit;
// Cet fonction il permet de  mettre à jour le fichier contenant les informations des voitures avec crédit
VoitureCredit * Miseajour_fic_voiture_credit(VoitureCredit *list_voit)
{
    // Déclaration d'un pointeur pour parcourir la liste
    VoitureCredit *p = list_voit;

    // Ouverture du fichier en mode écriture
    FILE *fic = fopen("ListeVoitureCredit.csv", "w");

    // Vérification de l'ouverture du fichier
    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    // Parcours de la liste des voitures avec crédit et écriture dans le fichier
    while(p != NULL)
    {
        // Écriture des informations de la voiture dans le fichier
        fprintf(fic, "%s;%.2f;%.2f;%d;%d/%d/%d\n", p->ID, p->PrixAchat,p->Apport, p->Duree,p->DateAchat.jj,p->DateAchat.mm,p->DateAchat.aaaa);
        p = p->suivant; // Passage à la voiture suivante dans la liste
    }

    // Fermeture du fichier
    fclose(fic);
}

//Cet fonction permet d'afficher les informations des voitures avec crédit
void AffichervoitCredit(VoitureCredit *liste) {
    // Déclaration d'un pointeur pour parcourir la liste
    VoitureCredit *p = liste;

    // Affichage de l'en-tête du tableau
    printf("%-10s | %-15s | %-15s | %-12s | %-11s \n", "ID", "Prix Achat", "Apport", "Duree", "Date Achat");
    printf("============================================================================================= \n");

    // Parcours de la liste des voitures avec crédit et affichage des informations
    while (p != NULL) {
        // Affichage des informations de la voiture
        printf("%-10s | %-15f | %-15f| %-12d | %-2d/%-2d/%-4d\n",
               p->ID, p->PrixAchat, p->Apport, p->Duree, p->DateAchat.jj, p->DateAchat.mm, p->DateAchat.aaaa);
        p = p->suivant; // Passage à la voiture suivante dans la liste
    }
}

// Cet fonction permet d'ajouter une voiture avec crédit à la liste
VoitureCredit *AjoutlistevoitureCredit(VoitureCredit *liste, char **ut)
{
    VoitureCredit *e, *p;
    char *dt; // Pointeur pour le découpage de la date
    int i;

    // Allocation de la mémoire pour la nouvelle voiture
    e = (VoitureCredit *)malloc(sizeof(VoitureCredit));

    // Lecture des données à partir du tableau ut
    strcpy(e->ID, ut[0]);// ut : tableau de chaînes de caractères contenant les informations de la voiture à ajouter
    e->PrixAchat = (float)atof(ut[1]);
    e->Apport = (float)atof(ut[2]);
    e->Duree = (int)atof(ut[3]);

    // Découpage de la date et attribution des valeurs aux membres de la structure Date
    dt = strtok(ut[4], "/");
    int j = 0;
    while (dt != NULL)
    {
        if (j == 0)
            e->DateAchat.jj = (int)atof(dt);
        if (j == 1)
            e->DateAchat.mm = (int)atof(dt);
        if (j == 2)
            e->DateAchat.aaaa = (int)atof(dt);
        dt = strtok(NULL, "/");
        j++;
    }

    // Si la liste est vide, la nouvelle voiture devient la première de la liste
    if (liste == NULL)
    {
        e->suivant = liste;
        liste = e;
    }
    else
    {
        // Sinon, recherche du dernier maillon de la liste pour y attacher la nouvelle voiture
        p = liste;
        while (p->suivant != NULL)
        {
            p = p->suivant;
        }
        e->suivant = NULL;
        p->suivant = e;
    }
    return liste;
}

// Cet fonction permet d'ajouter une voiture avec crédit à la liste à partir d'une nouvelle voiture avec crédit
VoitureCredit *AjoutvoitureCredit(VoitureCredit *liste, VoitureCredit *nov_voit)
{
    VoitureCredit *e, *p;

    // Allocation de la mémoire pour la nouvelle voiture
    e = (VoitureCredit *)malloc(sizeof(VoitureCredit));

    // Copie des données de la nouvelle voiture dans la nouvelle allocation de mémoire
    e = nov_voit;

    // Si la liste est vide, la nouvelle voiture devient la première de la liste
    if (liste == NULL)
    {
        e->suivant = liste;
        liste = e;
    }
    else
    {
        // Sinon, recherche du dernier maillon de la liste pour y attacher la nouvelle voiture
        p = liste;
        while (p->suivant != NULL)
        {
            p = p->suivant;
        }
        e->suivant = NULL;
        p->suivant = e;
    }
    return liste;
}


//Cet fonction permet de charger les voitures avec crédit à partir d'un fichier CSV dans une liste
VoitureCredit * chargervoituresCredit(VoitureCredit * lstvoitCredit)
{
    FILE *fic;
    char ligne[500];
    char *ptr_chaine;

    // Ouvrir le fichier CSV en mode lecture
    fic = fopen("ListeVoitureCredit.csv", "rt");

    // Vérifier si le fichier est ouvert avec succès
    if (fic == NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    // Lire chaque ligne du fichier CSV
    while (fgets(ligne, sizeof(ligne), fic) != NULL)
    {
        // Supprimer les retours chariot ou les nouvelles lignes de la ligne lue
        ligne[strcspn(ligne, "\r\n")] = '\0';

        // Découper la ligne en éléments séparés par des points-virgules
        ptr_chaine = strtok(ligne, ";");
        char *strut[5];
        int j = 0;

        // Stocker les éléments dans un tableau
        while (ptr_chaine != NULL)
        {
            strut[j++] = ptr_chaine;
            ptr_chaine = strtok(NULL, ";");
        }

        // Ajouter la voiture avec crédit à la liste à partir des données stockées dans le tableau
        lstvoitCredit = AjoutlistevoitureCredit(lstvoitCredit, strut);
    }

    // Fermer le fichier
    fclose(fic);

    // Retourner la liste des voitures avec crédit mise à jour
    return lstvoitCredit;
}

// Cet fonction permet de rechercher une voiture avec crédit dans la liste par son ID
int chercher_voiture_credit(VoitureCredit *liste, char *ID)
{
    VoitureCredit *p = liste;
    int IDtrouvee = 1;

    // Parcourir la liste des voitures avec crédit
    while (p != NULL)
    {
        // Comparer l'ID de la voiture actuelle avec l'ID recherché
        if (strcmp(p->ID, ID) == 0)
        {
            // Si l'ID est trouvé, mettre IDtrouvee à 0 et sortir de la boucle
            IDtrouvee = 0;
            break;
        }
        // Passer à la voiture suivante dans la liste
        p = p->suivant;
    }

    // Retourner l'indicateur indiquant si l'ID a été trouvé ou non
    return IDtrouvee;
}


// Cet fonction perment d'afficher les voitures avec crédit qui ont dépassé la durée de crédit
void Credit_terminer(VoitureCredit *listVoitCredit)
{  // Déclaration des variables pour la gestion du temps et du crédit
    float reste, traite;
    time_t current_time;
    struct tm *local_time;
    time_t user_time;
    struct tm user_tm;
    double diff_seconds;
    int diff_months;

    // Obtenir le temps actuel
    time(&current_time);
    local_time = localtime(&current_time);

    // Pointeur vers la première voiture avec crédit dans la liste
    VoitureCredit *p = listVoitCredit;

    // Affichage de l'en-tête du tableau
    printf("%-10s | %-15s | %-15s| %-12s | %-12s\n", "ID", "Prix Achat", "Apport", "Duree", "Date Achat");
    printf("=============================================================================================\n");

    // Parcourir la liste des voitures avec crédit
    while (p != NULL)
    {
        // Assigner la date d'achat de la voiture à la structure tm
        user_tm.tm_year = p->DateAchat.aaaa;
        user_tm.tm_mon = p->DateAchat.mm;
        user_tm.tm_mday = p->DateAchat.jj;
        user_tm.tm_year -= 1900; // Année - 1900 pour correspondre à la structure tm
        user_tm.tm_mon -= 1;     // Mois - 1 car les mois commencent à 0

        // Convertir la date d'achat en une représentation de temps
        user_time = mktime(&user_tm);

        // Calculer la différence en secondes entre la date d'achat et la date actuelle
        diff_seconds = difftime(user_time, current_time);

        // Convertir la différence en nombre de mois
        diff_months = (user_tm.tm_year - local_time->tm_year) * 12 + (user_tm.tm_mon - local_time->tm_mon);
        diff_months = diff_months * -1;

        // Vérifier si la durée du crédit a été dépassée
        if (diff_months > p->Duree)
        {
            // Afficher les détails de la voiture avec crédit dont la durée a été dépassée
            printf("%-10s | %-15.2f | %-15.2f| %-12d | %-2d / %-2d / %-4d\n",
                   p->ID, p->PrixAchat, p->Apport, p->Duree, p->DateAchat.jj, p->DateAchat.mm, p->DateAchat.aaaa);
        }

        // Passer à la voiture suivante dans la liste
        p = p->suivant;
    }
}

// Cet fonction permet de calculer et afficher le reste du crédit pour chaque voiture avec crédit
void ResteDeCredit(Voiture *list_voiture, VoitureCredit *listVoitCredit)
{
    // Déclaration des variables pour la gestion du temps et du crédit
    float reste, traite;
    time_t current_time;
    struct tm *local_time;
    time_t user_time;
    struct tm user_tm;
    double diff_seconds;
    int diff_months;

    // Obtenir le temps actuel
    time(&current_time);
    local_time = localtime(&current_time);

    // Pointeur vers la première voiture avec crédit dans la liste
    VoitureCredit *p = listVoitCredit;

    // Affichage de l'en-tête du tableau
    printf("%-10s | %-15s | %-15s| %-12s | %-12s | %-10s\n", "ID", "Prix Achat", "Apport", "Duree", "Date Achat", "Reste du credit");
    printf("=========================================================================================================================\n");

    // Parcourir la liste des voitures avec crédit
    while (p != NULL)
    {
        // Assigner la date d'achat de la voiture à la structure tm
        user_tm.tm_year = p->DateAchat.aaaa;
        user_tm.tm_mon = p->DateAchat.mm;
        user_tm.tm_mday = p->DateAchat.jj;
        user_tm.tm_year -= 1900; // Année - 1900 pour correspondre à la structure tm
        user_tm.tm_mon -= 1;     // Mois - 1 car les mois commencent à 0

        // Convertir la date d'achat en une représentation de temps
        user_time = mktime(&user_tm);

        // Calculer la différence en secondes entre la date d'achat et la date actuelle
        diff_seconds = difftime(user_time, current_time);

        // Convertir la différence en nombre de mois
        diff_months = (user_tm.tm_year - local_time->tm_year) * 12 + (user_tm.tm_mon - local_time->tm_mon);

        // Vérifier si la durée du crédit a été dépassée ou si le crédit est en cours
        if (diff_months > p->Duree || diff_months > 0)
        {
            reste = 0; // Le crédit est terminé ou en cours, donc aucun reste à payer
        }
        else
        {
            // Calculer le reste du crédit à payer
            diff_months = diff_months * -1;
            reste = (p->PrixAchat - p->Apport) - ((p->PrixAchat - p->Apport) / p->Duree) * diff_months;
        }

        // Afficher les détails de la voiture avec crédit et son reste à payer
        if (reste >= 0)
        {
            printf("%-10s | %-15.2f | %-15.2f| %-12d | %-2d / %-2d / %-4d| %-10.2f\n",
                   p->ID, p->PrixAchat, p->Apport, p->Duree, p->DateAchat.jj, p->DateAchat.mm, p->DateAchat.aaaa, reste);
        }

        // Passer à la voiture avec crédit suivante dans la liste
        p = p->suivant;
    }
}
#endif // GESTION_LEASING_H_INCLUDED
