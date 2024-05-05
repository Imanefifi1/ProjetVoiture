#ifndef STOCKER_H_INCLUDED
#define STOCKER_H_INCLUDED
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
void StockFile(FILE *f);
void afficherCSV(FILE *f);

void StockFile(FILE *f) {
    car *v;
    char ID[30];
    int rep = 0 ;
    f = fopen("Cars.csv", "a+"); // Ouvrir le fichier en mode append et lecture
    if (f == NULL) {
        printf("Probleme d'acces au fichier.\n");
        exit(1);
    }

    v = (car*)malloc(sizeof(car)); // Allouer de la mémoire pour une nouvelle voiture
    if (v == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        fclose(f);
        return;
    }

    printf("\n ID : ");
    scanf("%s", ID);
    getchar(); // Consommer le caractère de nouvelle ligne restant dans le tampon

    // Vérifier si l'ID existe déjà dans le fichier
    rewind(f); // Réinitialiser la position du curseur de fichier au début
    while (fscanf(f, " %29s", v->id) == 1) {
        if (strcmp(ID, v->id) == 0) {
        	rep = 1 ;
            printf("\n Cette ID existe deja !\n");
            break;
     }
        }
    if(rep == 0){
    strcpy(v->id, ID);

    printf("\n Marque : ");
    scanf("%s", v->marque);
    getchar(); // Consommer le caractère de nouvelle ligne restant dans le tampon

    printf("\n Nom utilisateur : ");
    scanf("%s", v->nom_utilisateur);
    getchar();

    printf("\n Modele : ");
    scanf("%s", v->modele);
    getchar();

    printf("\n Type de carburant : ");
    scanf("%s", v->type_carburant);
    getchar();

    printf("\n Nombre de places : ");
    scanf("%d", &v->nb_places);
    getchar();

    printf("\n Prix de location : ");
    scanf("%f", &v->prix_location);
    getchar();

    do {
        printf("\n Disponibilite (0: non disponible, 1: disponible) : ");
        scanf("%d", &v->status);
        getchar();
    } while (v->status < 0 || v->status > 1);

    fprintf(f, "%s\t%s\t%s\t%s\t%s\t%d\t%.2f\t%d\n", v->id, v->marque, v->nom_utilisateur, v->modele, v->type_carburant, v->nb_places, v->prix_location, v->status);
	}

    free(v); // Libérer la mémoire allouée pour la voiture
    fclose(f);
}
// Procédure qui affiche les infos des voitures stockées dans le fichier csv
void afficherCSV(FILE *f) {
    f = fopen("Cars.csv", "r"); // Choisir "Cars.csv" comme chemin d'accès pour lire ses données
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char line[100];
    fgets(line, sizeof(line), f); // Ignorer l'en-tête du fichier CSV

    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    fclose(f);
}


#endif // STOCKER_H_INCLUDED
