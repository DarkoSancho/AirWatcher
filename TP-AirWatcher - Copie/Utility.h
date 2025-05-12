/*************************************************************************
                           Utility  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Utility> (fichier Utility.h) ----------------
#ifndef UTILITY_H
#define UTILITY_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "User.h"

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Utility>
//
//
//------------------------------------------------------------------------

class Utility : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    static time_t convertToTimeT(const string& dateStr);
    static string convertToString(time_t time);
    static bool isWithinRadius(float lat1, float lon1, float lat2, float lon2, float radius);


//-------------------------------------------- Constructeurs - destructeur
    Utility();

    ~Utility();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

#endif // UTILITY_H

