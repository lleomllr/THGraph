#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <math.h>
#include <set>
#include <string.h>

using namespace std;

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
    /*if (P.empty() && X.empty() && trouver_kQuasiCliques(R, adj, k)) {
        cliques.push_back(R);
        return;
    }

    int pivot = choisirPivot(P, X, adj);
    set<int> P_minus_pivot_neighbours = P;

    if (pivot != -1) {
        for (int v : adj[pivot]) {
            P_minus_pivot_neighbours.erase(v);
        }
    }

    for (int v : P_minus_pivot_neighbours) {
        set<int> Rn = R, Pn, Xn;
        Rn.insert(v);

        set_intersection(P.begin(), P.end(),
                         adj[v].begin(), adj[v].end(),
                         inserter(Pn, Pn.begin()));

        set_intersection(X.begin(), X.end(),
                         adj[v].begin(), adj[v].end(),
                         inserter(Xn, Xn.begin()));

        BronKerbosch_kQCM(Rn, Pn, Xn, adj, cliques, k);

        P.erase(v);
        X.insert(v);
    }*/
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

    /*const int n = 100;
    const double d = 5.0;
    const double l = 200.0;
    const double h = 200.0;

    vector<set<int>> adj(n);
    genereDisque(n, d, l, h, adj);*/

    int n = 9;
    vector<set<int>> adj(n);

    //Exemple du sujet
    adj[0].insert(1); adj[0].insert(2); adj[0].insert(3); adj[0].insert(4); adj[0].insert(5);// A-C, A-D
    adj[1].insert(0); adj[2].insert(0); adj[3].insert(0); adj[4].insert(0); adj[5].insert(0);
    adj[1].insert(5); adj[5].insert(1);
    adj[2].insert(4); adj[4].insert(2);
    adj[2].insert(3); adj[3].insert(2);
    adj[3].insert(5); adj[5].insert(3);
    adj[4].insert(5); adj[5].insert(4);
    adj[4].insert(6); adj[6].insert(4);
    adj[5].insert(6); adj[6].insert(5);
    adj[5].insert(7); adj[7].insert(5);
    adj[5].insert(8); adj[8].insert(5);
    adj[6].insert(7); adj[7].insert(6);
    adj[7].insert(8); adj[8].insert(7);

    /*
    set<int> K, P, X;
    for (int i = 0; i < n; i++) {
        P.insert(i);
    }

    vector<set<int>> cliques;

    //BronKerbosch(K, P, X, adj, cliques);
    int s=1;
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

    vector<set<int>> adj(9);

    adj[0].insert(1); adj[0].insert(2); adj[0].insert(3); adj[0].insert(4); adj[0].insert(5);// A-C, A-D
    adj[1].insert(0); adj[2].insert(0); adj[3].insert(0); adj[4].insert(0); adj[5].insert(0);
    adj[1].insert(5); adj[5].insert(1);
    adj[2].insert(4); adj[4].insert(2);
    adj[2].insert(3); adj[3].insert(2);
    adj[3].insert(5); adj[5].insert(3);
    adj[4].insert(5); adj[5].insert(4);
    adj[4].insert(6); adj[6].insert(4);
    adj[5].insert(6); adj[6].insert(5);
    adj[5].insert(7); adj[7].insert(5);
    adj[5].insert(8); adj[8].insert(5);
    adj[6].insert(7); adj[7].insert(6);
    adj[7].insert(8); adj[8].insert(7);
*/
    for (int k = 0; k <= 2; ++k) {
        set<int> R, P, X;
        vector<set<int>> cliques;

        // Initialisez l'ensemble P avec tous les sommets du graphe
        for (int i = 0; i < adj.size(); ++i) {
            P.insert(i);
        }

        BronKerbosch_kQCM(R, P, X, adj, cliques, k);

        // Trouver la taille de la plus grande clique
        size_t maxSize = 0;
        for (const auto& clique : cliques) {
            if (clique.size() > maxSize) {
                maxSize = clique.size();
            }
        }

        // Afficher la taille de la plus grande k-quasi-clique
        cout << "La taille de la " << k << "-quasi-clique maximum est : " << maxSize << endl;
    }
    return 0;
}
