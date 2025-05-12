/*************************************************************************
                           Utility  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Utility> (fichier Utility.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>


//------------------------------------------------------ Include personnel
#include "Utility.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
time_t Utility::convertToTimeT(const string& dateStr)
{
    struct tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%d/%m/%Y");

    if (!ss.fail())
    {
        time_t time = mktime(&tm);
        cout << "CONVERTED TIME:" << convertToString(time) << endl;
        return time;
    }

    return 0; // Return 0 if the conversion fails
}

string Utility::convertToString(time_t time)
{
    struct tm *tm = localtime(&time);
    stringstream ss;
    ss << put_time(tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool Utility::isWithinRadius(float lat1, float lon1, float lat2, float lon2, float radius) {
   return true; 
}



//-------------------------------------------- Constructeurs - destructeur

Utility::Utility()
{
    // Constructeur par défaut
}

Utility::~Utility()
{
    // Destructeur
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Méthodes protégées
