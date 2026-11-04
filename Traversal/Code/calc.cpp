#include <iostream>
#include <vector>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;
using matrix = vector<vector<int>>;

cpp_int puissance(cpp_int a, long n)
{
    cpp_int resultat = 1;

    while (n > 0)
    {
        if (n % 2 == 1)
            resultat *= a;

        a *= a;
        n /= 2;
    }

    return resultat;
}

vector<int> operator*(matrix const& M, vector<int> const& V) {
    vector<int> resultat(M.size(), 0);
    for (size_t i = 0; i < M.size(); i++) {
        for (size_t j = 0; j < M[i].size(); j++) {
            resultat[i] += M[i][j] * V[j];
        }
    }
    return resultat;
}

ostream& operator<<(ostream& os, const vector<int>& V) {
    os << "[";
    for (size_t i = 0; i < V.size(); i++) {
        if (i > 0) os << ", ";
        os << V[i];
    }
    os << "]";
    return os;
}

matrix initialisation_mat(int n){
    //Initialise une matrice n,n avec des 0.
    matrix init = {};
    for (int i =0; i<= n-1; i++){
        init.push_back({});
        for (int j =0; j<= n-1; j++){
            init[i].push_back(0);
        }
    }
    return init;
}

bool est_nulle(vector<int> l){
    //Vérifie si une liste est composée uniquement de 0.
    for (int i=0; i<=l.size()-1; i++){
        if (l[i]!=-2){
            return false;
        }
    }
    return true;
}

vector<int> init_comptage(int n){
    //Construit un vecteur de n-1 éléments qui sont tous des 2.
    vector<int> initial = {};
    for(int i=1; i<=n-1; i++){
        initial.push_back(2);
    }
    return initial;
}

vector<int> decrement(vector<int> l){
    //Retire 1 à l'écriture en base 5 d'un nombre ( ici les coefficient vont de -2 à 2 ).
    int i = l.size()-1;
    while(l[i]==-2){
        i--;
    }
    l[i]-=1;
    for(int j = l.size()-1; j>=i+1; j--){
        l[j]=2;
    }
    return l;
}

vector<vector<int>> gen_C_n(int n){
    //Génére toutes les suites de marches de longueur n-1.
    vector<vector<int>> C_n = {};
    C_n.push_back(init_comptage(n));
    while(not(est_nulle(C_n.back()))){
         C_n.push_back(decrement(C_n.back()));
    }
    return C_n;
}

int norme_1(vector<int> l){
    //Calcule la norme 1 d'un vectueur.
    int res = 0;
    for( size_t i = 0; i<l.size(); i++ ){
        res+= abs(l[i]);
    }
    return res;
}

int nb_compatible(vector<int> a){
    //revoie le nombre de suites de marches compatible avec a 
    vector<int> F = {1,1,1,1,1}; // Il y a autant de 1 que de taille de marche possible ( cf. étude mathématique ) dans le cas calssique c'est 5.
    for ( size_t i = 0; i < a.size(); i++){
        matrix M_i = initialisation_mat(5);
        for (int ligne =0; ligne<= 4; ligne++){
            for (int colone =0; colone<= 4; colone++){
                if (abs(a[i] + (colone) - (ligne)) <=2){ // On vérifie la condition de proximité ( cf. étude mathématique ).
                    M_i[ligne][colone]=1;
                }
                else{
                    M_i[ligne][colone]=0;
                }
            }
        }
        F = M_i * F;
    }
    return norme_1(F);
}

int main(){
    int n = 10;
    vector<vector<int>> C_n=gen_C_n(n);
    ifstream fichier("valeurs_C_a.txt");
    cpp_int valeur;
    cpp_int somme = 0; 
    cpp_int somme_2=0;
    cpp_int min = C_n.size(); // On sait par définition que tous les |C_a| sont inférieurs à |C_n| 
    while ( fichier >> valeur){
        somme+=valeur;
        somme_2+=puissance(valeur,2);
        if (min > valeur){
            min=valeur;
        }
    }
    //A la fin, somme est le nombre de jeux à 2 colonnes et n lignes et somme_2 est le nombre de jeux à trois colonnes et n lignes.
    cout << " borne inf = " << min*puissance(somme_2,4)/puissance(C_n.size(),3) << '\n' << " borne sup = " << puissance(somme_2,3)*C_n.size();
    return 0; 
}
