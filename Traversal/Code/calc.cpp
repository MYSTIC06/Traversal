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
    for (int i=0; i<=l.size()-1; i++){
        if (l[i]!=-2){
            return false;
        }
    }
    return true;
}

vector<int> init_comptage(int n){
    vector<int> initial = {};
    for(int i=1; i<=n-1; i++){
        initial.push_back(2);
    }
    return initial;
}

vector<int> decrement(vector<int> l){
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
    //génére toutes les suites de marches de longueur n-1 (ie les colones de longeurs n qui commences par 0)
    vector<vector<int>> C_n = {};
    C_n.push_back(init_comptage(n));
    while(not(est_nulle(C_n.back()))){
         C_n.push_back(decrement(C_n.back()));
    }
    return C_n;
}

int norme_1(vector<int> l){
    int res = 0;
    for( size_t i = 0; i<l.size(); i++ ){
        res+= abs(l[i]);
    }
    return res;
}

int nb_compatible(vector<int> a){
    //revoie le nombre de suites de marches compatible à droite avec a 
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

vector<int> oppose(vector<int> l){
    for (size_t i=0; i<l.size(); i++ ){
        l[i]=-l[i];
    }
    return l;
}

int main(){
    vector<vector<int>> C_n=gen_C_n(10);
    ifstream fichier("valeurs.txt");
    cpp_int valeur;
    cpp_int somme = 0;
    cpp_int somme_2=0;
    while ( fichier >> valeur){
        somme_2+=valeur;
        somme+=puissance(valeur,2);
    }
    cout << " somme = " << somme << '\n' << " borne = " << puissance(somme,3)*25*109591;
    return 0; 
}