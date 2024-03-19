#include <stdio.h>
#include <stdint.h>
#include <time.h>

//-----------------EXERCICE 1---------------------------//
void generegraphe(int n, int m, int arete[][2])
{
    srand(time(NULL)); 

    for(int i = 0; i < m; i++)
    {
        arete[i][0] = rand()%n; 
        arete[i][1] = rand()%n; 
    }
}

void affichage_tab(int tm, int tab[][2])
{
    int i, j; 
    for(i=0; i < tm; i++)
    {
        printf("["); 
        for(j=0; j < 2; j++)
        {
            printf("%d ", tab[i][j]); 
            if(j==0) printf(","); 
        }
        printf("]"); 
    }
    printf("\n"); 
}


//--------------------EXERCICE 2-------------------------------//
void compoConnexes(int n, int m, int arete[][2])
{
    int comp[0]; 

    for(int x = 0; x < n; x++)
    {
        comp[x] = x; 
    }
    for(int x = 0; x < m; x++)
    { 
        if(comp[arete[x][1]] != comp[arete[x][0]]){
            int c = comp[arete[x][0]]; 
            for(int z = 0; z < n; z++)
            {
                if(comp[z] == c) comp[z] = comp[arete[x][0]]; 
            }
        }
    }
}

//------------------EXERCICE 3---------------------------------//
int tailleComp(int n, int m, int arete[][2])
{
    int taille[0]; 
    int comp = compoConnexes(n,m,arete); 
    int occu = 0; 

    for(int x = 0; x < n; x++)
    {
        for(int i=0; i < m; i++){
            if(comp[i] == x) ++occu; 
        }
        taille[x] = occu; 
    }
    return taille; 
}

int max_elem(int arete[][2], int n, int m)
{
    int max = arete[m][2]; 
    for(int i=0; i < n; i++)
    {
        if(arete[i][2] > max) max = arete[i][2]; 
        
    }
    return max; 
}

int NbCompo(int n, int m, int arete[][2])
{
    int occu = 0; 
    int maximum = max_elem(arete, n, m); 
    for(int x = 0; x <= maximum; x++)
    {
        for(int i = 0; i < m; i++)
        {
            if(arete[i] == x) ++occu; 
            if(occu != 0) printf("Il y a %d composantes de taille %d", occu, x); 
        }
    }
}


int main()
{
    srand(time(NULL)); 

    int n = 10000; 
    int m = 5000; 
    int arete[m][2]; 

    /*generegraphe(n, m, arete); 
    affichage_tab(m, arete); 
    
    compoConnexes(n, m, arete); 
    */
    tailleComp(n, m, arete); 
    NbCompo(n, m, arete); 


    return 0; 
}