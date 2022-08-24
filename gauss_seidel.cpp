/*
*   RAHENINTSOA
*   Maminirina
*   L3 MISA 2020-2021
*   nirinaramamy1@gmail.com
*   +261 34 23 944 07
*/

/*---------------------------------
Pour compiler le programme :

g++ maminirina.cpp -o maminirina
./maminirina

---------------------------------*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<float>> MatrixF;
typedef vector<float> VectorF;

void createVector(VectorF& X, int dimension);
void getData(MatrixF& A, VectorF& B);
void showVector(VectorF& vector);
void showSystem(MatrixF A, VectorF B);
void gaussSeidel(MatrixF& A, VectorF& X, VectorF& B);
int getDimensionFromData();


int main() {
    MatrixF A;
    VectorF X;
    VectorF b;

    int N = getDimensionFromData();

    getData(A, b);
    createVector(X, N);

    cout << "Le système d'équation A.X = b est : " << endl << endl;
    showSystem(A, b);

    cout << endl << endl;
    cout << "En appliquant à ce système d'équation l'algorithme de Gauss-Seidel" << endl;
    gaussSeidel(A, X, b);

    cout << "On obtient une approximation de X : " << endl << endl;
    showVector(X);
    

    return EXIT_SUCCESS;
}

void createVector(VectorF& X, int dimension) {
    for(int i = 0; i < dimension; i++) {
        X.push_back(0);
    }
}

void showSystem(MatrixF A, VectorF B) {
    for(int i = 0; i < A.size(); i++) {
        cout << '|';
        for(int j = 0; j < A.size(); j++) {
            if(j == A.size()-1) {
                cout << A[i][j] << '|';
            } else {
                cout << A[i][j] << setw(10);
            }
        }
        cout << setw(5) << "|X" << i+1 << '|' <<  setw(3) << '=' << setw(5) << B[i] << endl;
    }
}

void showVector(VectorF& vector) {
    for(int i = 0; i < vector.size(); i++) {
        cout << setw(5) << "|X" << i+1 << '|' <<  setw(3) << '=' << setw(10) << setprecision(3) <<vector[i] << endl;
    }
}

void gaussSeidel(MatrixF& A, VectorF& X, VectorF& B) {
    VectorF residu;
    int N = getDimensionFromData();
    createVector(residu, N);

    float r{0}; //Contiendra la somme des valeurs absolues de residu[i]
    float epsilon = 10e-6; //Prennons epsilon 10^-6
    
    // On initialise tous les X[i] à 1;
    for(int i = 0; i < N; i++) {
        X[i] = 1;
    }

    // On calcul le résidu r
    for(int i = 0; i < N; i++) {
        float s = 0;
        for(int k = 0; k < N; k++) {
            s += A[i][k] * X[k];
        }
        residu[i] = B[i] - s;
        r += fabs(residu[i]);
    }

    // Calcul des approximations de X[i]
    while(r > epsilon){
        for(int i = 0; i < N; i++){
            float s{0};
            for(int k = 0; k < N; k++){
                s += A[i][k] * X[k];
            }
            residu[i] = B[i] - s;
            X[i] += (1.0 / A[i][i]) * residu[i];
        }

        r = 0;
        for(int i = 0; i < N; i++){
            r += fabs(residu[i]);
        }
    }
}

int getDimensionFromData() {
    ifstream inFile{"data.txt"};
    string data{""};
    int N{0};
    if(inFile.is_open()) {
        inFile >> data;
        N = stoi(data);
    }
    inFile.close();
    return N;
}

void getData(MatrixF& A, VectorF& B) {
    //Récupérer les données
    ifstream inFile{"data.txt"};
    string data{""};
    VectorF X;
    int N{0};

    if(inFile.is_open()) {
        //Récupérer la dimension
        inFile >> data;
        N = stoi(data);

        //Récupérer la matrice
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                inFile >> data;
                X.push_back(stof(data));
            }
            A.push_back(X);
            X.clear();
        }

        //Récupérer le vecteur
        for(int i = 0; i < N; i++) {
            inFile >> data;
            B.push_back(stof(data));
        }
    }
    inFile.close();
}