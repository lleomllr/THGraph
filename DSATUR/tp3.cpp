#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

const int n=25; // nombre de sommets
int adj[n][n];  // matrice d'adjacence du graphe
int couleur1[n]; 
int couleur2[n];
int couleur3[n];   // couleurs des sommets pour l'agorithme exact
bool trouve=false; // permet de stopper l'algorithme exact
                   // quand une coloration  a ete trouvee


bool convient(int x, int c)
{
    for(int i=0;i<x;i++){
        if(adj[x][i] && (couleur1[i]==c)) return false;
    }
    return true;
}

bool convient2(int x, int c)
{
    for(int i=0;i<x;i++){
        if(adj[x][i] && (couleur2[i]==c)) return false;
    }
    return true;
}

bool convient3(int x, int c)
{
    for(int i=0;i<n;i++){
        if(adj[x][i] && (couleur3[i]==c)) return false;
    }
    return true;
}


void colorRR(int x, int k)
{ 
    if(x==n)
    { 
        cout << "Coloration en " << k << " couleurs trouvee" << endl;
        for(int i=0;i<n;i++) cout << "couleur de " << i << " : " << couleur1[i] << endl; //int z;cin >> z;
        trouve=true;
    }
    else{
        for(int c=1;c<=k;c++){
            if(convient(x,c)){
                couleur1[x]=c;
                colorRR(x+1,k);
	            if(trouve) return;
            }
        }
    }
}

void colorExact(int k)
{
    for(int i=0;i<n;i++){
        couleur1[i]=0;
        colorRR(0,k);
        if(!trouve) cout << "Pas de coloration en " << k <<" couleurs" << endl;
    }
}

//--------------------EXERCICE 1---------------------

void generegraphe(int p)
{
    for(int x=0; x<n; x++)
    {
        for(int y=x+1; y<n; y++)
        {
            int proba = rand()%100; 
            if(proba <= p)
            {
                adj[x][y] =  1; 
                adj[y][x] = 1; 
            }
        }
    }
}

void afficheGraphe()
{
    for(int x=0; x<n; x++)
    {
        cout << "sommet n " << x <<" : "; 
        for(int y = 0; y<n; y++)
        {
            if(adj[x][y] == 1) cout <<"voisin" << y << "  "; 
        }
        cout << endl; 
    }
    
}

//-----------------EXERCICE 2-----------------------------------

int nbChromatique()
{
    bool found = false; 
    int k = 1; 
    while(!found)
    {
        colorExact(k); 
        found = trouve; 
        k+=1; 
    }
    return --k; 
}

//----------------EXERCICE 3------------------------------------

int colorGlouton()
{
    for(int x = 0; x<n; x++)
    {
        couleur2[x] = 0; 
    }

    int max = 1; 
    for(int x = 0; x<n; x++)
    {
        bool found = false; 
        int c = 1; 
        while(!found)
        {
            found = convient2(x, c); 
            c+=1; 
        }
        couleur2[x]=--c; 
        if(c > max) max = c;
    }
    return max; 
}

//------------------------EXERCICE 4-----------------------------------

int DSATUR_choix_sommet(int DSAT[], bool coul3_colorier[])
{
    int sommet = 0; 
    int DSATmax = -1; 
    bool conflit = false; 
    
    for(int x = 0; x<n; x++)
    {
        if(!coul3_colorier[x])
        {
            if(DSAT[x] > DSATmax)
            {
                DSATmax = DSAT[x]; 
                sommet = x; 
                conflit = false; 
            }else if(DSAT[x] == DSATmax) conflit = true; 
        }
    }

    if(conflit)
    {
        int degreMax = -1; 
        for(int x = 0; x<n; x++)
        {
            if(!coul3_colorier[x] && DSAT[x] == DSATmax)
            {
                int courantDeg = 0; 
                for(int y = 0; y < n; y++)
                {
                    if(x!=y && adj[x][y] == 1) courantDeg+=1; 
                }
                if(courantDeg > degreMax)
                {
                    degreMax = courantDeg; 
                    sommet = x; 
                }
            }
            
        }
    }
    return sommet; 
}

int DSATUR()
{
    int couleurMax = -1; //stock le nbre de couleur utilisée
    int DSAT[n]; //stock le degré de saturation de chaque sommet
    bool coul3_colorier[n]; //indqie si sommet colorié

    for(int x = 0; x<n; x++)
    {
        coul3_colorier[x] = false; 
    }

    int sommet = 0; 
    int colored = 0; 
    while(colored < n) //jusqu'a ce que tous les sommets soient coloriés
    {
        sommet = DSATUR_choix_sommet(DSAT, coul3_colorier); 
        bool coulUtiliser[n]; 
        
        for(int x = 0; x<n; x++)
        {
            coulUtiliser[x] = false; 
        }

        //maj du tab en fct des couleurs d"jà utilisées par ces voisins
        for(int y = 0; y<n; y++)
        {
            if(adj[sommet][y]==1 && coul3_colorier[y])
            {
                coulUtiliser[couleur3[y]] = true; 
                DSAT[sommet]+=1; 
            }
        }

        int couleur = 0; 
        while(coulUtiliser[couleur])
        {
            couleur+=1; 
        }

        couleur3[sommet] = couleur; 
        if(couleur > couleurMax) couleurMax = couleur; 

        coul3_colorier[sommet] = true; 
        colored+=1; 
    };
    return couleurMax; 
}

int main()
{
    generegraphe(30);
    //afficheGraphe();  

    int nbChro = nbChromatique(); 
    cout << "Nombre Chromatique : " << nbChro << endl; 

    int glouton = colorGlouton(); 
    cout << "Nombre de couleurs utilisées après glouton : "<< glouton << endl; 

    int dsatur = DSATUR(); 
    cout << "Nombre de couleurs utilisées après DSATUR : "<< dsatur << endl; 
    return 0; 
}