#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <set>
#include <string.h>

using namespace std;

const int k=2; // nombre de sommets
int adjaM[k][k];
int s;

struct Point {
    double x, y;
};

struct Disque {
    Point centre;
    double rayon;
};

void ecrire_cliquesMax(const vector<set<int>>& cliques, const string& fich)
{
    ofstream file(fich);
    if (!file.is_open()) {
        cout << "Erreur d'ouverture du fichier." << endl;
        return;
    }
    for (const auto& clique : cliques) {
        for (int vertex : clique) {
            file << vertex << " ";
        }
        file << endl;
    }
    file.close();
}

//-------------------K-QuasiCliques----------------------------------------------//

int trouver_kQuasiCliques(set<int>& R, const vector<set<int>>& adja, int k)
{
    int aretesNonCo = 0;

    for(int i : R)
    {
        for(int j : R)
        {
            if(i!=j && (adja[i].find(j) == adja[j].end()))
            {
                aretesNonCo++;
            }
        }
    }
    aretesNonCo /= 2;

    return aretesNonCo <= k;
}

void BronKerbosch_kQCM(set<int>& R, set<int>& P, set<int>& X, const vector<set<int>>& adj, vector<set<int>>& cliques, int k) {
    if (P.empty() && X.empty() && trouver_kQuasiCliques(R, adj, k)) {
        cliques.push_back(R);
        return;
    }

    for (int v : P) {
        set<int> Rn = R, Pn, Xn;
        Rn.insert(v);

        for (int voisins : adj[v]) {
            if (P.find(voisins) != P.end()) {
                Pn.insert(voisins);
            }
        }

        for (int voisins : adj[v]) {
            if (X.find(voisins) != X.end()) {
                Xn.insert(voisins);
            }
        }

        BronKerbosch_kQCM(Rn, Pn, Xn, adj, cliques, k);

        P.erase(v);
        X.insert(v);
    }
}

//-----------------------------------Test Graphes de disque G(d,h,l,n)------------------------------//

bool intersect(const Disque& d1, const Disque& d2)
{
    double dist = sqrt(pow(d1.centre.x - d2.centre.x, 2) + pow(d1.centre.y - d2.centre.y, 2));
    return dist < (d1.rayon + d2.rayon);
}

void genereDisque(int n, double d, double l, double h, vector<set<int>>& adj)
{
    vector<Disque> disques(n);
    double rayon = d/2.0;

    for(int i=0; i<n; i++)
    {
        disques[i].centre.x = (double)rand() / RAND_MAX * l;
        disques[i].centre.y = (double)rand() / RAND_MAX * h;
        disques[i].rayon = rayon;
    }

    adj.resize(n);
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(intersect(disques[i], disques[j]))
            {
                adj[i].insert(j);
                adj[j].insert(i);
            }
        }
    }
}

//----------------------------------------------------------------------------------------//

int main() {
    //srand(time(NULL));

    const int n = 100;
    const double d = 5.0;
    const double l = 200.0;
    const double h = 200.0;*/

    vector<set<int>> adj(n);
    genereDisque(n, d, l, h, adj);

    /*int p = 50;
    generegraphe(p);*/

    vector<set<int>> adj(k);
    /*for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            if (adjaM[i][j] == 1) {
                adj[i].insert(j);
            }
        }
    }*/

    //int n = 5;
    

    /*adj[0].insert(1); adj[1].insert(0); //arête entre les sommets 0 et 1
    adj[0].insert(4); adj[4].insert(0);
    adj[1].insert(4); adj[4].insert(1);
    adj[1].insert(2); adj[2].insert(1);
    adj[2].insert(3); adj[3].insert(2);
    adj[3].insert(5); adj[5].insert(3);
    adj[4].insert(3); adj[3].insert(4);*/

    //Exemple du cours
    /*adj[0].insert(1); adj[1].insert(0); //arête entre les sommets 0 et 1
    adj[0].insert(2); adj[2].insert(0);
    adj[0].insert(3); adj[3].insert(0);
    adj[0].insert(4); adj[4].insert(0);
    adj[0].insert(5); adj[5].insert(0);
    adj[1].insert(6); adj[6].insert(1);
    adj[2].insert(3); adj[3].insert(2);
    adj[2].insert(4); adj[4].insert(2);
    adj[3].insert(5); adj[5].insert(3);*/
    adj[0].insert(1); adj[1].insert(0);
    adj[0].insert(2); adj[2].insert(0);
    adj[1].insert(2); adj[2].insert(1);
    adj[1].insert(3); adj[3].insert(1);
    adj[1].insert(4); adj[4].insert(1);
    adj[2].insert(3); adj[3].insert(2);
    adj[3].insert(4); adj[4].insert(3);


    set<int> K, P, X;
    for (int i = 0; i < n; i++) {
        P.insert(i);
    }

    vector<set<int>> cliques;
  
    BronKerbosch_kQCM(K, P, X, adj, cliques, s);

    size_t maxT = 0;
    for (const auto& clique : cliques) {
        for(int v : clique)
        {
            if (clique.size() > maxT) {
                maxT = clique.size();
            }
        }
    }
    cout << "Taille de la plus grande clique: " << maxT << endl;

    ecrire_cliquesMax(cliques, "cliques_maximales.txt");

    return 0;
}
