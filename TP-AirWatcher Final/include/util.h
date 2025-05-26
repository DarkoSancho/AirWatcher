/*************************************************************************
                           util  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Xxx> (fichier Xxx.h) ----------------
#if ! defined ( UTIL_H )
#define UTIL_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Util>
//
//
//------------------------------------------------------------------------
#include "Date.h"
class Util 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    float getAverage (vector<float> vector);

    float getAverage (list<int> list);
    
    float getMin (vector<float> vector);

    pair<Date, int> getMin(map<Date,int>);

    float getMax(vector<float> vector);

    float getMax(list<float> list);

    pair<Date, int> getMax(map<Date,int>);

    float getSdeviation(vector<float> vector);

    float getNExceedances(vector<float> vector, float th);

    float getATMO(vector<float> vector);

    int indiceO3(float v); 

    int indiceNO2(float v); 

    int indiceSO2(float v);

    int indicePM10(float v);
//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

    Util ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Util ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // XXX_H

