/*************************************************************************
                           Xxx  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Xxx> (fichier Xxx.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <list>
#include <stdexcept>
//------------------------------------------------------ Include personnel
#include "util.h"
#include "Date.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
float Util::getAverage(std::vector<float> vector)
{
    int somme = 0;
    for (std::vector<float>::iterator it = vector.begin(); it != vector.end(); ++it)
    {
        somme += *it;
    }

    if (vector.empty()){
        return 0; // pour éviter une division par zéro
    }

    return somme / vector.size();
}

float Util::getAverage (list<int> list){
    int somme = 0;
    for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        somme += *it;
    }

    if (list.empty()){
        return 0; // pour éviter une division par zéro
    }

    return somme / list.size();
}

float Util::getMin(std::vector<float> vector){
    return *std::min_element(vector.begin(), vector.end());
}

pair<Date,int> Util::getMin(map<Date, int> map) {
    if (map.empty()) {
        throw std::runtime_error("La map est vide !");
    }
    auto itMin = map.begin();
    for (auto it = map.begin(); it != map.end(); ++it) {
        if (it->second < itMin->second) {
            itMin = it;
        }
    }
    return *itMin;
}

float Util::getMax(std::vector<float> vector){
    return *std::max_element(vector.begin(), vector.end());
}

float Util::getMax(std::list<float> list){
    return *std::max_element(list.begin(), list.end());
}

pair<Date,int> Util::getMax(map<Date, int> map) {
    if (map.empty()) {
        throw std::runtime_error("La map est vide !");
    }
    auto itMax = map.begin();
    for (auto it = map.begin(); it != map.end(); ++it) {
        if (it->second > itMax->second) {
            itMax = it;
        }
    }
    return *itMax;
}

float Util::getSdeviation(std::vector<float> vector){
    float av = getAverage(vector);
    float variance = 0.0;

    for (float val : vector){
        variance += (val -av)*(val - av);
    }

    return sqrt(variance/vector.size());
}

float Util::getNExceedances(vector<float> vector, float th){
    int ex = 0;
    if (th == -1){
        return -1;
    }
    for (std::vector<float>::iterator it = vector.begin(); it != vector.end(); ++it)
    {
        if (*it >= th){
            ex ++;
        }
    }
    return ex;

}

int Util::indiceO3(float v) {
    if (v <= 29) return 1;
    else if (v <= 54) return 2;
    else if (v <= 79) return 3;
    else if (v <= 104) return 4;
    else if (v <= 129) return 5;
    else if (v <= 149) return 6;
    else if (v <= 179) return 7;
    else if (v <= 209) return 8;
    else if (v <= 239) return 9;
    else return 10;
}

int Util::indiceNO2(float v) {
    if (v <= 29) return 1;
    else if (v <= 54) return 2;
    else if (v <= 84) return 3;
    else if (v <= 109) return 4;
    else if (v <= 134) return 5;
    else if (v <= 164) return 6;
    else if (v <= 199) return 7;
    else if (v <= 274) return 8;
    else if (v <= 399) return 9;
    else return 10;
}

int Util::indiceSO2(float v) {
    if (v <= 39) return 1;
    else if (v <= 79) return 2;
    else if (v <= 119) return 3;
    else if (v <= 159) return 4;
    else if (v <= 199) return 5;
    else if (v <= 249) return 6;
    else if (v <= 299) return 7;
    else if (v <= 399) return 8;
    else if (v <= 499) return 9;
    else return 10;
}

int Util::indicePM10(float v) {
    if (v <= 6) return 1;
    else if (v <= 13) return 2;
    else if (v <= 20) return 3;
    else if (v <= 27) return 4;
    else if (v <= 34) return 5;
    else if (v <= 41) return 6;
    else if (v <= 49) return 7;
    else if (v <= 64) return 8;
    else if (v <= 79) return 9;
    else return 10;
}

//-------------------------------------------- Constructeurs - destructeur



Util::Util ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Util>" << endl;
#endif
} //----- Fin de Xxx


Util::~Util ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Util>" << endl;
#endif
} //----- Fin de ~Xxx


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

