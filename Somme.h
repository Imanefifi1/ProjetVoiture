#ifndef SOMME_H_INCLUDED
#define SOMME_H_INCLUDED

float SommeRep (float p){
	int n, i;
	float S = 0;
	printf (" \n\n                                               Faites entrer le nombres de pieces a reparer : ");
	scanf("%d",&n);
	for(i=1 ; i <= n ; i++){
		printf("                                                Saisir le prix de la piece %d : ",i);
		scanf("%f", &p);
		 S = S + p;
	}
	printf("\n                                               La somme estimee pour reparer cette voiture est : %.2f MAD \n\n",S);
	return S;
}

#endif // SOMME_H_INCLUDED
