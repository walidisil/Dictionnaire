typedef struct noeud * arbre;
typedef struct noeud {
     char* Mot;
     arbre fg;
     arbre fd;
     arbre pere;
 }noeud;
int compare(const void *a, const void *b);
char ** LireFileToTab(FILE *f,int* taille);
long milieu(FILE *dico, long debut, long fin);
long existe(char* mot,FILE*dico);
char * trouverMot(char * mot, FILE * dico);
void MotsHorsdico(FILE *file, FILE *dico);
char ** lirefile(FILE*dico,int*taille);
long milieutab(long debut,long fin);
int existeTab (char**tab,char*mot,int taille);
char* trouverMottab(char *mot,char**tab,int taille);
void MotsHorsdicotab(FILE *file, char** dico,int taille);
arbre createNode(char *);
arbre LireFileTree(FILE *);
arbre existeTree (arbre, char *,arbre*);
void insertKey (arbre ,char*);
void MotHorsDicoTree(arbre file1,arbre dico1);
char * trouveMotArbre(char * mot,arbre racine);
long milieu(FILE *dico,long debut,long fin) {
    char buffer[8000];
    char c = 's';
    fseek(dico,(debut + fin)/2,0);
    fgets(buffer,8000,dico);
    while (c != '\n')
    {
        fseek(dico,-2,1);
        c = fgetc(dico);
    }
    fseek(dico,-3,1);
    c = 's';
    while (c != '\n')
    {
        fseek(dico,-2,1);
        c = fgetc(dico);
    }
    return ftell(dico);
}

long existe(char*mot,FILE*dico)
{
    char tempBuffer[1024];

    rewind(dico);

    fseek(dico,0,SEEK_SET);

    long debut=(long)ftell(dico);

    fgets(tempBuffer,sizeof(tempBuffer),dico);
    char*tok=strtok(tempBuffer,":");

    if(strcmp(mot,tok)==0){
    return 0;
    }


    fseek(dico,0,SEEK_END);
    long fin=(long)ftell(dico);
    //for returning to start of line
    char c =fgetc(dico);
    int x=-1;
    while(c!='\n'){
        x=x-1;
        fseek(dico,x,SEEK_END);
        c=fgetc(dico);
    }

    long pos=(long)ftell(dico);
    fgets(tempBuffer,sizeof(tempBuffer),dico);
    tok=strtok(tempBuffer,":");

    if(strcmp(mot,tok)==0){
    return pos;
    }

    rewind(dico);

    long middle;long middle2;
    while(debut<=fin &&!feof(dico)){
        middle=debut+(fin-debut)/2;
        if(middle==middle2){
            return -1;
        }

        fseek(dico,middle,SEEK_SET);

        x=0;
        c='c';
        while(c!='\n'){
            x=x-1;
            fseek(dico,middle+x,SEEK_SET);
            c=fgetc(dico);
        }
        pos=(long)ftell(dico);
        fgets(tempBuffer,sizeof(tempBuffer),dico);
        tok=strtok(tempBuffer,":");

        if(strcmp(mot,tok)==0){
            return pos;
            }
        else if(strcmp(mot,tok)>0){

                x=0;
                c='c';
                while(c!='\n'){
                    x=x+1;
                    fseek(dico,middle+x,SEEK_SET);
                    c=fgetc(dico);
                }
                debut=(long)ftell(dico);

                fgets(tempBuffer, sizeof(tempBuffer),dico);
                tok=strtok(tempBuffer,":");

                if(strcmp(mot,tok)==0){
                return debut;
                }
            }
            else{

                x=0;
                c='c';
                while(c!='\n'){
                x=x-1;
                fseek(dico,middle+x,SEEK_SET);
                c=fgetc(dico);
                }
                fin=(long)ftell(dico);

                fgets(tempBuffer,sizeof(tempBuffer),dico);
                tok=strtok(tempBuffer,":");

                if(strcmp(mot,tok)==0){
                return fin;
                }
            }
            middle2=middle;
    }
    return -1;
}

char * trouverMot(char * mot, FILE * dico) {
    rewind(dico);
    int position = existe(mot,dico);
    if (position==-1)
    {
        return "";
    }else
    {
    fseek(dico,position,0);
    char *temp;
    temp = (char *) malloc(sizeof(char) * 100000);
    fgets(temp,100000,dico);
    return temp;
    
    }
       
}

void MotsHorsdico(FILE *file, FILE *dico) {
    char c[1000];
    char chunk[1000];
    rewind(file);
    while (!feof(file))
    {
        fseek(file,-1,1);
        fgets(c,1000,file);
        fseek(file,-strlen(c)-1,1);
        fgets(chunk,strlen(c),file);
        fgetc(file);
        for (int j = 0; j < strlen(c); j++)
        {
            chunk[j] = toupper(chunk[j]); 
        }
        
        if(existe(chunk,dico) == -1) {
            
            printf("%s\n",chunk);
        }
        fgetc(file);
    }
    
}

               //FONCTION TABLEAU
char ** lirefile(FILE*dico,int *taille){

 char **tab;
 tab=(char**)malloc(sizeof(char*)*100000);
 int i=0;
 rewind(dico);
 while (!feof(dico))
 {   tab[i]=(char*)malloc(sizeof(char)*100000);
     fgets(tab[i],100000,dico);
     i++;
 }
 *taille=i;
 rewind(dico);
 return tab;
}

long milieutab(long debut,long fin){
   return(((debut+fin)/2)+1);
}

int existeTab (char**tab,char*mot,int taille){
    int debut,fin,mid;
    fin=taille-1;
    debut=0;
    char t[10000];
    while (debut<=fin)
    {
        mid=(debut+fin)/2;
        strcpy(t,tab[mid]);
       if (strcmp(mot,strtok(t,":")) == 0)
       {
        return mid+1;
       } else {
              if (strcmp(mot,strtok(t,":"))>0)
              {
                debut=mid+1;
              }
              else
              {
                fin=mid-1;
              }
        }
        
    }
    return -1;
}

char* trouverMottab(char *mot,char**tab,int taille){
int pos;
pos = existeTab(tab,mot,taille);
if (pos == -1)
{
return "";
}else
{
return tab[pos-1];
}
}

void MotsHorsdicotab(FILE *file, char **dico,int taille)
{
    char chunk[7000];
    char c[7000];
    rewind(file);
  while (!feof(file))
   {  
      fseek(file,-1,1);
        fgets(c,7000,file);
        fseek(file,-strlen(c)-1,1);
        fgets(chunk,strlen(c),file);
        fgetc(file);
        for (int j = 0; j < strlen(c); j++)
        {
            chunk[j] = toupper(chunk[j]); 
        } 
    if (existeTab(dico,strtok(chunk,":"),taille-1) == -1){

           for (int j = 0; j < strlen(c); j++)
        {
            chunk[j] = tolower(chunk[j]); 
        }    
            printf("%s\n",chunk);
        }
        fgetc(file);
    }
  } 

              //FONCTION ARBRE
arbre createNode(char * word) {
    arbre newNode = (arbre) malloc(sizeof(noeud));
    newNode->fd = NULL;
    newNode->fg = NULL;
    newNode->pere = NULL;
    newNode->Mot = word;
    return newNode;
}

arbre LireFileTree(FILE *dico) {
    rewind(dico);
    char **temp;
    int i = 2;
    temp = (char **) malloc(sizeof(char *) * 900000);
    temp[0] = (char *) malloc(sizeof(char) * 1000);
    temp[1] = (char *) malloc(sizeof(char) * 1000);
    fgets(temp[0],10000,dico);
    arbre racine =  createNode(temp[0]);
    fgets(temp[1],10000,dico);
    arbre fils1 =  createNode(temp[1]);
    fils1->pere = racine;
    racine->fg = fils1;
    while (!feof(dico))
    {
        temp[i] = (char *) malloc(sizeof(char) * 10000);
        fgets(temp[i],10000,dico);
        insertKey(racine,temp[i]);
        i++;
    }
    free(temp);
    return racine;   
}

char * trouveMotArbre(char * mot,arbre racine) {
    arbre* pere;
    pere = (arbre*) malloc(sizeof(arbre));
    arbre pos = existeTree(racine,mot,pere);
    if(pos == NULL) {
        free(pere);
        free(pos);
        return "";
    } else {
        char *temp;
        temp = (char *) malloc(sizeof(char) * 10000);
        strcpy(temp,pos->Mot);
        free(pere);
        free(pos);
        return temp;
    }
}

void MotHorsDicoTree(arbre file1,arbre dico1) {
    arbre* test;
    arbre word;
    char chunk[1000];
    test = (arbre*) malloc(sizeof(arbre));
    word = (arbre) malloc(sizeof(noeud));
    if(file1) {
        strcpy(chunk,file1->Mot);
        strtok(chunk,"\n");
        for (int j = 0; j < strlen(chunk); j++)
        {
            chunk[j] = toupper(chunk[j]); 
        }
        
        word = existeTree(dico1,chunk,test);
        if( word == NULL) printf("%s", file1->Mot);
        MotHorsDicoTree(file1->fg,dico1);
        MotHorsDicoTree(file1->fd,dico1);
    }
}

arbre existeTree (arbre racine, char * cle,arbre* pere) {

    int i = 0;
    *pere = NULL;
    char temp[10000];
    while (i==0) {
        strcpy(temp,racine->Mot);
        strtok(temp,":");
        if (strcmp(temp,cle) == 0) {
            return (racine);
        }
        *pere = racine->pere;
        strcpy(temp,racine->Mot);
        strtok(temp,":");
        if (strcmp(temp,cle)>0) {
            if(racine->fg == NULL) {
                *pere = racine;
                return NULL;
            } else {
                    racine = racine->fg;
                    *pere = racine->pere;
                }
        } else {
            if(racine->fd == NULL) {
                *pere = racine;
                return NULL;
            } else {
                racine = racine->fd;
                *pere = racine->pere;
                }
        }
    }
}

void insertKey (arbre racine ,char* mot){
    arbre p,aux,pos;
    pos = createNode("");
    aux = existeTree(racine,mot,&pos);
    p = createNode(mot);
    if (racine == NULL)
    {
        racine = p;
    } else if(strcmp(pos->Mot,mot) > 0)
    {
        pos->fg = p;
    } else {
        pos->fd = p;
    }
    free(aux);
}
int compare(const void *a, const void *b) 
{ 
    char* p = *(char**)a;
    char* q = *(char**)b;
    char* p2,*q2;
    strcpy(p2,p);
    strcpy(q2,q);
    strtok(p2,":");
    strtok(q2,":");
    return strcmp(p2, q2);
} 

char ** LireFileToTab(FILE *f,int* taille) {
    char **tab;
    tab = (char **) malloc(sizeof(char *) * 900000); 
    int i = 0;
    rewind(f);
    while (!feof(f))
    {
        tab[i] = (char *) malloc(sizeof(char) * 100000);
        fgets(tab[i],100000,f);
        i++;
    }
    *taille = i;
    rewind(f);
    return tab;
}