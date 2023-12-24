#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include <ctype.h>
#include "headers.h"
int main()
{
char sortir,sortir1;
char* MotTrouver;
MotTrouver = (char * )malloc(sizeof(char) * 10000);
int l;
int taille;
// FILE *Nontrie=fopen("NonTrieDico.txt","r");
// int t;
// char **tab = LireFileToTab(Nontrie,&t);
// FILE *Trie=fopen("DictionnaireTrie.txt","w");
// FILE *file=fopen("Externe.txt","r");
// char** TabDeFichierTrie = lirefile(Trie,&taille);
// arbre arbreDico = LireFileTree(Nontrie);
// arbre nouvelleArbre= LireFileTree(file);
FILE *f;
f=fopen("NonTrieDico.txt","r");
int t;
char **tab = LireFileToTab(f,&t);
printf("%s",tab[0]);
qsort(tab,t,sizeof(char*),compare);
printf("%s",tab[0]);
FILE* f2 = fopen("DictionnaireTrie.txt","w");
int i = 0;
for (size_t i = 0; i < t; i++)
{
    fputs(tab[i],f2);
}
free(tab);


 printf("                              /// Bienvenue dans le dictionnaire! \\\\\\                             \n");
 printf("Choisissez parmis les strucures suivante: \n");
do
{   printf("POUR DICTIONNAIRE TRIE :\n");
    printf("-1 pour Fichier \n");
    printf("-2 pour Tableau \n");
    printf("POUR DICITONNAIRE NON TRIE :\n");
    printf("-3 pour Arbre binaire \n");
    scanf("%d",&l);
    switch (l)
    {
    case 1:
        do
        { int y;
            printf("Si vous chercher a l'aide d'un MOT ou d'un FICHIER EXTERNE \n");
            printf("-1 MOT \n");
            printf("-2 FICHIER EXTERNE \n");
            scanf("%d",&y);
            switch (y)
            {
                case 1:
                    char Mot[1000];
                    printf("Donnez le mot voulue :");
                    scanf("%s",Mot);
                    for (int i = 0; i < strlen(Mot); i++)
                    {
                        Mot[i]=toupper(Mot[i]);
                    }
                    strcpy(MotTrouver,trouverMot(Mot,Trie));
                    if(strcmp(MotTrouver,"") == 0) printf("Mot introuvable \n");
                    else printf("Ton mot est : \n%s",MotTrouver);
                    
                    break;
                case 2:
                MotsHorsdico(file,Trie);
                    break;

                default:
                   printf("S'il vous plait entrez un chiffre entre 1 et 2");
                   break;
            }
            printf("VOULEZ VOUS SORTIR ? APPUYER SURE 'O'/'o' SINON AUTRE BOUTON \n");
            scanf("  %c",&sortir);
            
        } while (sortir!='o' && sortir!='O');
        break;
    case 2:
    do
    {  int y;
        printf("Si vous chercher a l'aide d'un MOT ou d'un FICHIER EXTERNE\n");
        printf("-1 POUR MOT\n");
        printf("-2 POUR FICHIER EXTERNE\n");
        scanf("%d",&y);
        switch (y)
        {
        case 1:
                char Mot[1000];
                printf("Donnez le mot voulue : ");
                scanf("%s",Mot);
                for (int i = 0; i < strlen(Mot); i++)
                {
                    Mot[i]=toupper(Mot[i]);
                }
                strcpy(MotTrouver,trouverMottab(Mot,TabDeFichierTrie,taille));
                if (strcmp(MotTrouver,"") != 0) printf("Ton mot est : \n%s",MotTrouver);
                else printf("Mot introuvable \n");
                
            break;
        case 2:
        MotsHorsdicotab(file,TabDeFichierTrie,taille-1);
            break;
        default:
           printf("S'il vous plait entrez un chiffre entre 1 et 2 \n");
            break;
        }

        printf("VOULEZ VOUS SORTIR ? APPUYER SURE 'O'/'o' SINON AUTRE BOUTON \n");
        scanf(" %c",&sortir);

    } while (sortir!='o' && sortir!='O');
        break;
    case 3:
    do
    { int y;
        printf("Si vous chercher a l'aide d'un MOT ou d'un FICHIER EXTERNE\n");
        printf("-1 MOT\n");
        printf("-2 FICHIER EXTERNE\n");
        scanf("%d",&y);
        switch (y)
        {
        case 1:
            char Mot[100];
            printf("Entre le Mot voulue : ");
            scanf("%s",Mot);
            for (int i = 0; i < strlen(Mot); i++)
            {
                Mot[i] = toupper(Mot[i]);
            }
            
            strcpy(MotTrouver,trouveMotArbre(Mot,arbreDico));
            if (strcmp(MotTrouver,"") != 0) printf("Le mot est : \n%s",MotTrouver);
            else printf("Mot introuvable \n");
            break;
        case 2:
        MotHorsDicoTree(nouvelleArbre,arbreDico);
            break;
        default:
            printf("S'il vous plait entrez un chiffre entre 1 et 2 \n");
            break;
        }
        printf("VOULEZ VOUS SORTIR DE L'ARBRE BINAIRE ?? entre 'o'/'O'SINON AUTRE BOUTON \n");
        scanf(" %c",&sortir);        
    } while (sortir != 'O' && sortir != 'o');    
        break;
    default:
        printf("S'il vous plait entre 1 et 3 !");
        break;
    }   
    printf("VOULEZ VOUS QUITTER L'APPLICATION ?? 'o'/'O' SINON AUTRE BOUTON \n");
        scanf(" %c",&sortir1);
} while (sortir1!='o' && sortir1!='O');
     free(MotTrouver);
     return 0;
}

