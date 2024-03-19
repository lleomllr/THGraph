#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;
		
const int n=40;               // Le nombre de points.
const int dmax=220;		        // La distance jusqu'a laquelle on relie deux points.
vector<int> voisin[n];          // Les listes de voisins.                    
int point[n][2];                // Les coordonnees des points.
int arbre[n-1][2];              // Les aretes de l'arbre de Dijkstra .
int pere[n];    		        // La relation de filiation de l'arbre de Dijkstra.

  


void afficheGraphe(int n,int d, int sommet[][2])
{
    ofstream output;             // Cree le fichier Graphe.ps qui affiche le graphe.
    output.open("Graphe.ps",ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << endl; 

    for(int i=0;i<n;i++)
    {
        output << sommet[i][0] << " " << sommet[i][1] << " 1 0 360 arc" <<endl;
        output << "0 setgray" <<endl;
        output << "fill" <<endl;
        output << "stroke"<<endl;
        output << endl;
    }
    output << endl;

    for(int i=0;i<n-1;i++)
    {
        for (int j=i+1 ;j<n;j++){
            if ((sommet[i][0]-sommet[j][0])*(sommet[i][0]-sommet[j][0])+(sommet[i][1]-sommet[j][1])*(sommet[i][1]-sommet[j][1])<d*d){
                output << sommet[i][0] << " " << sommet[i][1] << " moveto" << endl;
                output << sommet[j][0] << " " << sommet[j][1] << " lineto" << endl;
                output << "stroke" << endl;
                output << endl;
            }
        }
    }
}

void afficheArbre(int n, int k, int point[][2], int arbre[][2]){
    ofstream output;                           
    output.open("Arbre.ps",ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << "%%BoundingBox: 0 0 612 792" << endl;
    output << endl;  

    for(int i=0;i<n;i++){
        output << point[i][0] << " " << point[i][1] << " 1 0 360 arc" <<endl;
        output << "0 setgray" <<endl;
        output << "fill" <<endl;
        output << "stroke"<<endl;
        output << endl;
    }

    output << endl;

    for(int i=0;i<k;i++){
        output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] << " moveto" << endl;
        output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] << " lineto" << endl;
        output << "stroke" << endl;
        output << endl;
    }
    output.close();
}

//--EXERCICE 1--//

void generegraphe(int n, int point[][2])
{
    for(int x = 0; x < n; x++)
    {
        point[x][0] = rand()%611; 
        point[x][1] = rand()%791; 
    }
}

//--EXERCICE 2--//

void voisins()
{
    for(int i = 0; i < n; i++)
    {
        vector<int> voisini; 
        for(int j=0; j < n; j++)
        {
            if(i!=j)
            {
                int dist_euclid = sqrt(pow((point[i][0]-point[j][0]),2)+pow((point[i][1]-point[j][1]),2)); 
                if(dist_euclid == dmax) voisini.push_back(j); 
            }
        }
        voisin[i] = voisini;
    }
}

//--EXERCICE 3--DIJKSTRA//

int nbm = 0; //nb de sommet marqué
int l[n]; //dist source
int m[n]; //sommet marqué => 0 = pas marqué / 1 = marqué

void Disjkstra_un(int sommet)
{
    for(int x = 0; x < n; x++)
    {
        if(x!=sommet)
        {
            int dist_euclid = sqrt(pow((point[sommet][0]-point[x][0]),2)+pow((point[sommet][1]-point[x][1]),2)); 
            if(dist_euclid <= dmax)
            {
                l[x] = dist_euclid; 
                pere[x] = sommet; 
            }else{
                l[x] = dmax*n*10; 
                pere[x] = -1; 
            }
        }
    }
}

int Dijkstra_choix_s(int sommet)
{
    //sommet à distance minimale de s et non marqué
    int min = -1; 
    int min_dist = -1; 
    for(int x = 0; x < n; x++)
    {
        if(m[x]==0 && (min_dist==-1 || l[x] < min_dist))
        {
            min = x; 
            min_dist = l[x]; 
        }
    }

    if(min!=-1)
    {
        m[min]=1; 
        nbm+=1; 
        return min; 

    }else{
        cout << "min = -1" << endl; 
        return -1; 
    }
}

void Dijkstra(int s)
{
    pere[s]=-2; 
    Disjkstra_un(s); 
    l[s] = 0; 
    m[s] = 1; 
    nbm+=1; 

    while(nbm < n)
    {
        int sommet = Dijkstra_choix_s(s); 
        for(int y = 0; y < n; y++)
        {
            if(y!=sommet && m[y]==0)
            {
                int dist_euclid = sqrt(pow((point[sommet][0]-point[y][0]),2)+pow((point[sommet][1]-point[y][1]),2)); 
                if(dist_euclid <= dmax && l[y] > l[sommet] + dist_euclid)
                {
                    pere[y] = sommet; 
                    l[y] = l[sommet] + dist_euclid; 
                }
            }
        }
    }
}

void afficheDijkstra()
{
    for(int x = 0; x < n; x++)
    {
        cout << "Distance du sommet " << x << " depuis la source : " << l[x] << endl; 
    }
}

//--EXERCICE 4--//

int construitArbre()
{
    int i = 0; 
    for(int x = 0; x < n; x++)
    {
        if(pere[x] >= 0)
        {
            arbre[i][0] = x; 
            arbre[i][1] = pere[x]; 
            i++; 
        }
    }
    return i; 
}

int main(){
    generegraphe(n, point); 
    afficheGraphe(n, dmax, point);
    
    int source = 36; 
    Dijkstra(source); 
    afficheDijkstra(); 
    
    int aretes = construitArbre(); 
    afficheArbre(n, aretes, point, arbre); 
    return 0; 
}