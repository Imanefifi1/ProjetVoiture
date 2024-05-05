#ifndef ECRAN_ACC_H_INCLUDED
#define ECRAN_ACC_H_INCLUDED


void ecran_acc(void)
{
    int i;
    system("cls");
    printf("\033[0;00m");//Couleur:Blanc
    printf("%c",201);


    for(i=0;i<103;i++)
    {
        printf("%c",205);
        Sleep(10);
    }

        printf("%c",187);
        printf("\n");

    for(i=0;i<13;i++)
    {
        switch (i)
        {

         case 4 :
            Sleep(10);
            printf("%c",186);
            printf("\033[0;31m");

            printf("\t\t\tEMSI : %ccole Marocaine des Sciences de l%cIng%cnieur",144,39,130);
            printf("\033[0;00m");

            printf("\t\t\t\t%c",186);
            printf("\n");
            break ;

        case 6 :
            Sleep(10);
            printf("%c",186);
            printf("\033[0;31m");

            printf("\t\t\t\tMini Projet : Location De Voitures");
            printf("\033[0;00m");

            printf("\t\t\t\t\t%c",186);
            printf("\n");
            break ;
        case 8 :
            Sleep(10);
            printf("%c",186);
            printf("\033[0;31m");

            printf("\t\t\t\tR%calis%c par: Marwa Boully\tImane Hachefi",130,130);
            printf("\033[0;00m");

            printf("\t\t\t\t%c",186);
            printf("\n");
            break ;

        default :
            Sleep(10);
            printf("%c",186);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t%c",186);
            printf("\n");

        }
    }
 printf("%c",200);
for(i=0;i<103;i++)
    {
        printf("%c",205);
    }
        printf("%c",188);
        printf("\n");

}





#endif // ECRAN_ACC_H_INCLUDED
