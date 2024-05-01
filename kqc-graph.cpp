#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Graph {
public:
    int n;  // Nombre de sommets
    vector<set<int>> adj;  // Liste d'adjacence

    Graph(int size) : n(size), adj(size) {}

    void ajout_aretes(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    // Fonction pour vérifier si un ensemble de sommets est une k-quasi-clique
    bool est_KQuasiClique(const set<int>& candidat, double gamma) {
        for (int v : candidat) {
            int compt = 0;
            for (int u : candidat) {
                if (v != u && adj[v].find(u) != adj[v].end()) {
                    compt++;
                }
            }
            if (compt < gamma * (candidat.size() - 1)) return false;
        }
        return true;
    }

    // Fonction pour trouver toutes les k-quasi-cliques et les arêtes manquantes
    vector<pair<set<int>, vector<pair<int, int>>>> trouver_KQuasiCliques(int k, double gamma) {
        vector<pair<set<int>, vector<pair<int, int>>>> res;
        for (int i = 0; i < n; ++i) {
            set<int> candidat {i};

            // Étendre le candidat avec des sommets qui sont suffisamment connectés
            for (int j = 0; j < n; ++j) {
                if (i != j && adj[i].find(j) != adj[i].end()) {
                    int deg = 0;
                    for (int v : candidat) {
                        if (adj[j].find(v) != adj[j].end()) deg++;
                    }
                    if (deg >= gamma * (candidat.size() + 1) - 1) {
                        candidat.insert(j);
                    }
                }
            }

            // Vérifier si le candidat final est une quasi-clique
            if (candidat.size() >= k && est_KQuasiClique(candidat, gamma)) {
                vector<pair<int, int>> aretes_manq;
                // Trouver les arêtes manquantes
                for (auto u = candidat.begin(); u != candidat.end(); ++u) {
                    auto next = u;
                    ++next;
                    for (auto v = next; v != candidat.end(); ++v) {
                        if (adj[*u].find(*v) == adj[*u].end()) {
                            aretes_manq.emplace_back(*u, *v);
                        }
                    }
                }
                res.emplace_back(candidat, aretes_manq);
            }
        }
        return res;
    }
};

int main() {
    // Exemple du cours
    Graph g(9);
    g.ajout_aretes(0, 1); g.ajout_aretes(0, 2); g.ajout_aretes(0, 3); g.ajout_aretes(0, 4); g.ajout_aretes(0, 5);
    g.ajout_aretes(1, 5); g.ajout_aretes(2, 4); g.ajout_aretes(2, 3); g.ajout_aretes(3, 5); g.ajout_aretes(4, 5);
    g.ajout_aretes(4, 6); g.ajout_aretes(5, 6); g.ajout_aretes(5, 7); g.ajout_aretes(5, 8); g.ajout_aretes(6, 7);
    g.ajout_aretes(7, 8);

    // Paramètres
    int k = 3;
    double gamma = 0.4;  // 80% de densité

    // Trouver et afficher les k-quasi-cliques et les arêtes manquantes
    auto res = g.trouver_KQuasiCliques(k, gamma);
    for (const auto& [clique, aretes_manq] : res) {
        cout << "Quasi-Clique trouvée: {";
        for (int v : clique) {
            cout << v << " ";
        }
        cout << "}\n";
        if (!aretes_manq.empty()) {
            cout << "Missing edges: ";
            for (const auto& [u, v] : aretes_manq) {
                cout << "(" << u << ", " << v << ") ";
            }
            cout << "\n";
        }
    }

    return 0;
}




