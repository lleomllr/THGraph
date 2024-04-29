#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <set>
#include <string.h>

using namespace std;

//----------------------------QUESTION 1------------------------------------------//

int choix_pivot(const set<int>& P, const set<int>& X, const vector<set<int>>& adj) {
    int pivot = -1;
    size_t maxVoisins = 0;

    for (const auto& v : P) {
        size_t tailleVoisins = 0;
        for (int w : adj[v]) {
            if (P.find(w) != P.end()) {
                tailleVoisins++;
            }
        }
        if (tailleVoisins > maxVoisins) {
            pivot = v;
            maxVoisins = tailleVoisins;
        }
    }
    return pivot;
}

void BronKerbosch(set<int>& K, set<int>& P, set<int>& X, const vector<set<int>>& adj, vector<set<int>>& cliques) {
    if (P.empty() && X.empty()) {
        cliques.push_back(K);
        return;
    }

    int pivot = choix_pivot(P, X, adj);
    set<int> P_sans_vpivot;

    if (pivot != -1) {
        for (int v : P) {
            if (adj[pivot].find(v) == adj[pivot].end()) {
                P_sans_vpivot.insert(v);
            }
        }
    } else {
        P_sans_vpivot = P;
    }

    for (int v : P_sans_vpivot) {
        set<int> Kn = K, Pn, Xn;
        Kn.insert(v);


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

        BronKerbosch(Kn, Pn, Xn, adj, cliques);

        P.erase(v);
        X.insert(v);
    }
}

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

//--------------------------AJOUTS POUR QUESTION 2-------------------------------//

const int k=2; // nombre de sommets
int adjaM[k][k];
int s;

//reprise du code du TP3
void generegraphe(int p)
{
    for(int i = 0; i<k; i++)
    {
        for(int j = 0; j <k; j++)
        {
            adjaM[i][j] = 0;
        }
    }

    for(int x=0; x<k; x++)
    {
        for(int y=x+1; y<k; y++)
        {
            int proba = rand()%100;
            if(proba <= p)
            {
                adjaM[x][y] =  1;
                adjaM[y][x] = 1;
            }
        }
    }
}

int main() {
    //srand(time(NULL));

    /*int p = 50;
    generegraphe(p);*/

    //vector<set<int>> adj(k);
    /*for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            if (adjaM[i][j] == 1) {
                adj[i].insert(j);
            }
        }
    }*/

    int n = 5;
    vector<set<int>> adj(n);

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

    BronKerbosch(K, P, X, adj, cliques);

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
