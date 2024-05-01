struct Point {
    double x, y;
};

struct Disque {
    Point centre;
    double rayon;
};

bool intersection(const Disque& d1, const Disque& d2)
{
    double dist = sqrt(pow(d1.centre.x - d2.centre.x, 2) + pow(d1.centre.y - d2.centre.y, 2));
    return dist < (d1.rayon + d2.rayon);
}

//adaptation de la fonction du tp2
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
            if(intersection(disques[i], disques[j]))
            {
                adj[i].insert(j);
                adj[j].insert(i);
            }
        }
    }
}

int main()
{
  srand(time(0));
  int n = 40;       // Nombre de disques
  double diametre = 20.0; // Diametre de chaque disque
  double long = 40.0;  // Longueur de la zone
  double haut = 40.0;  // Hauteur de la zone

  vector<set<int>> adj;
  genereDisque(n, diametre, long, haut, adj);

  set<int> R, P, X;
  for (int i = 0; i < n; i++) P.insert(i);

  vector<set<int>> cliques;
  BronKerbosch(R, P, X, adj, cliques);

  for (const auto& clique : cliques) {
      for (int vertex : clique) {
          cout << vertex << " ";
      }
      cout << endl;
  }

  return 0;
}
