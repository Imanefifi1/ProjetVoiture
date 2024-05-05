#ifndef GESTION_PANNES_H_INCLUDED
#define GESTION_PANNES_H_INCLUDED
typedef struct VoiturePannes
{
    char ID[50];
    char ID_Panne[50];
    int Degre_endmg;
    float prix;
    struct VoiturePannes *suivant;
}VoiturePannes;

// Cette fonction affiche les pannes disponibles pour une voiture spécifique
void Afficher_Panne_dispo(VoiturePannes* liste, char *IDvoit) {
    VoiturePannes *p = liste; // Initialisation d'un pointeur pour parcourir la liste des pannes
    // Affichage de l'en-tête du tableau des pannes
    printf("%-10s | %-10s | %-20s | %-15s \n", "ID", "ID Panne", "Degree Endommagee", "Prix");
    printf("==================================================================================\n");
    // Parcours de la liste des pannes
    while (p != NULL) {
        // Vérification si la panne est associée à la voiture spécifique
        if(strcmp(p->ID, IDvoit) == 0)
            // Affichage des détails de la panne
            printf("%-10s | %-10s | %-15d%| %-15f \n", p->ID, p->ID_Panne, p->Degre_endmg, p->prix);
        p = p->suivant; // Passage au maillon suivant dans la liste des pannes
    }
}


int  chercher_panne(char *ID  )
{
     int IDtrouvee=0;

      FILE *fic;
    char ligne[1000];
    char * code_panne ;

        //fic = fopen("C:\\Users\\appst\\Desktop\\cours 2024\\programmation c\\projet location voitures\\Liste_Voiture.csv", "rt");
        fic = fopen("Listes_des_pannes.txt", "rt");

    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    while (fgets(ligne, sizeof(ligne), fic) != NULL) {
        ligne[strcspn(ligne, "\r\n")] = '\0';  // Supprime le retour chariot ou la nouvelle ligne
        code_panne=strtok(ligne,":");
        if (strcmp(code_panne,ID)==0)
        {
            IDtrouvee=1 ;
            break ;
        }
    }
    close(fic);
    return IDtrouvee ;
}
//Cet fonction permet de supprimer une panne selon l'ID
VoiturePannes* supprimer_Panne_IDPannes(VoiturePannes* liste, char *code,char *codePanne)
 {
   VoiturePannes* voitPannCourante = liste;
    VoiturePannes* voitPannPrecedente = NULL;

    // Cas où une panne à supprimer est en tête de liste
    if (voitPannCourante != NULL && strcmp(voitPannCourante->ID , code)==0 && strcmp(voitPannCourante->ID_Panne , codePanne)==0) {
        liste = voitPannCourante->suivant;
        free(voitPannCourante);
        return;
    }

    // Parcours de la liste pour trouver le panne à supprimer
    while (voitPannCourante != NULL && strcmp(voitPannCourante->ID, code)!=0 && strcmp(voitPannCourante->ID_Panne, codePanne)!=0) {
        voitPannPrecedente = voitPannCourante;
        voitPannCourante = voitPannCourante->suivant;
    }

    // Cas où le panne à supprimer est en milieu ou en fin de liste
    if (voitPannCourante == NULL) {
        printf("Le voiture avec le code %d n'a pas ete trouvee.\n", code);
        printf("Le panne avec le code %d n'a pas ete trouvee.\n", codePanne);
        return voitPannCourante;
    }

    voitPannPrecedente->suivant = voitPannCourante->suivant;
    free(voitPannCourante);
    return liste ;

 }

/*VoiturePannes* supprimer_Panne_IDPannes(VoiturePannes *liste, char *ID_Panne)
{
    VoiturePannes *p3=liste;
    int i,pos=-1 ;
    while(p3!=NULL)
    {
        if(strcmp(p3->ID_Panne,ID_Panne)==0)
        {
            break;
        }
        pos++ ;
        p3=p3->suivant ;
    }
    VoiturePannes *p2,*p=liste;
    if(liste==NULL)
	{ return liste;	}
    if(pos==1)
    {
    	liste=p->suivant;
    	free(p);
    	return liste;
	}
	while(p!=NULL)
	{
		i++;
		if(pos-1==i) break;
		p=p->suivant;
	}
	if(p==NULL || p->suivant==NULL)
	{
		printf("Panne introuvable!");
		return liste;
	}
	else
	{
		p2=p->suivant;
		p->suivant=p2->suivant;
		free(p2);
		printf("Suppression effectuee avec succes...");
		return liste;
	}
}*/
VoiturePannes * Miseajour_fic_voiture_Pannes(VoiturePannes *list_voit)
{
	VoiturePannes *p = list_voit;
     FILE *fic = fopen("PannesVoiture.csv", "w");

    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
while(p!=NULL)
{
    fprintf(fic, "%s;%s;%d;%.2f\n", p->ID, p->ID_Panne,p->Degre_endmg, p->prix);
    p=p->suivant ;
}
    fclose(fic);
}
void AffichervoitPannes(VoiturePannes *liste, char *ID) {
    VoiturePannes *p = liste;
    printf("%-10s | %-10s | %-20s | %-15s \n", "ID", "ID Panne", "Degree Endommagee", "Prix");
    printf("=========================================================================================================\n");
    while (p != NULL) {
            if(strcmp(p->ID,ID)) printf("%-10s | %-10s | %-15d%| %-15f \n",p->ID, p->ID_Panne, p->Degre_endmg, p->prix);
        p = p->suivant;
    }
}

VoiturePannes *Ajout_liste_voiturePannes(VoiturePannes *liste, char **ut)
{
     VoiturePannes *e, *p;
    // Allocation de la memoire
    e = (VoiturePannes *)malloc(sizeof(VoiturePannes));
    // Lecture des donnÃ©️es
    strcpy(e->ID, ut[0]);
    strcpy(e->ID_Panne, ut[1]);
    e->Degre_endmg=(int)atof(ut[2]);
    e->prix=(float) atof(ut[3]);
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


VoiturePannes *Ajout_voiturePannes(VoiturePannes *liste, VoiturePannes *nov_voitPannes)
{
     VoiturePannes *e, *p;
    // Allocation de la memoire
    e = (VoiturePannes *)malloc(sizeof(VoiturePannes));
    // Lecture des données
    e = nov_voitPannes; // Copie des données de la nouvelle voiture
    if (liste == NULL) {
        e->suivant = liste; // Mettre la nouvelle voiture en tête de liste si elle est la première
        liste = e; // Mettre à jour le pointeur de début de liste
    } else {
        // Recherche du dernier maillon
        p = liste;
        while (p->suivant != NULL) {
            p = p->suivant;
        }
        e->suivant = NULL; // Définir le successeur de la nouvelle voiture à NULL car elle est ajoutée à la fin de la liste
        p->suivant = e; // Relier la nouvelle voiture à la liste existante
    }
    return liste; // Retourner la liste mise à jour
}


    VoiturePannes * chargervoituresPannes(VoiturePannes * lstvoitPannes)
{
    FILE *fic;
    char ligne[500];
    char *ptr_chaine;

    fic = fopen("PannesVoiture.csv", "rt");

    if (fic == NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    while (fgets(ligne, sizeof(ligne), fic) != NULL)
    {
        ligne[strcspn(ligne, "\r\n")] = '\0';  // Supprime le retour chariot ou la nouvelle ligne
        ptr_chaine = strtok(ligne, ";");
        char *strut[4];  // Vous avez besoin d'un tableau pour stocker les Ã©️lÃ©️ments
        int j = 0;
        while (ptr_chaine != NULL)
        {
            strut[j++] = ptr_chaine;
            ptr_chaine = strtok(NULL, ";");
        }
        int i ;

        lstvoitPannes =Ajout_liste_voiturePannes(lstvoitPannes, strut);
    }
    close(fic);
    return lstvoitPannes ;
    }



// Cette fonction modifie le prix d'une panne identifiée par son ID
void *Modifier_voiture_Pannes(VoiturePannes *liste, char *IDmodifier, float Prix_Panne) {
    VoiturePannes *p = liste; // Initialisation d'un pointeur de type VoiturePannes pour parcourir la liste
    int IDtrouvee = 0; // Variable pour indiquer si l'ID de la panne a été trouvé

    // Parcours de la liste des pannes
    while (p != NULL) {
        // Vérification si l'ID de la panne correspond à celui recherché
        if (strcmp(p->ID_Panne, IDmodifier) == 0) {
            // Modification du prix de la panne si une valeur différente de -1 est spécifiée
            if (Prix_Panne != -1) {
                p->prix = Prix_Panne;
            }

            // Affichage d'un message indiquant que la modification a été effectuée avec succès
            printf("Modification effectuee avec succes...\n");
            IDtrouvee = 1; // Marquage de l'ID trouvé
            break; // Sortie de la boucle de recherche
        }
        p = p->suivant; // Passage au maillon suivant dans la liste
    }
}


// Cette fonction affiche la liste des pannes à partir d'un fichier texte
void liste_pannes() {
    FILE *fic; // Déclaration d'un pointeur de fichier
    char ligne[1000]; // Tableau pour stocker une ligne lue du fichier

    // Ouverture du fichier contenant la liste des pannes en mode lecture
    fic = fopen("Listes_des_pannes.txt", "rt");

    // Vérification si l'ouverture du fichier a réussi
    if (fic == NULL) {
        printf("Ouverture fichier impossible !");
        exit(0); // Arrêt du programme en cas d'échec de l'ouverture du fichier
    }

    // Affichage de l'en-tête de la liste des pannes
    printf("Id : Libelle\n");
    printf("--------------------------------------\n");

    // Lecture du fichier ligne par ligne jusqu'à la fin du fichier
    while (fgets(ligne, sizeof(ligne), fic) != NULL) {
        ligne[strcspn(ligne, "\r\n")] = '\0';  // Supprime le retour chariot ou la nouvelle ligne
        printf("%s\n", ligne); // Affichage de la ligne lue du fichier
    }

    fclose(fic); // Fermeture du fichier
}





#endif // GESTION_PANNES_H_INCLUDED
