/*************************************************************************
                           PrivateIndividual  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <PrivateIndividual> (fichier PrivateIndividual.h) ----------------
#ifndef PRIVATEINDIVIDUAL_H
#define PRIVATEINDIVIDUAL_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include "User.h"

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateIndividual>
//
//
//------------------------------------------------------------------------

class PrivateIndividual : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // Getters
    list<string> getSensorID() const;
    float getPoints() const;

    // Setters
    void setSensorID(const list<string>& sensorID);
    void setPoints(float points);


//-------------------------------------------- Constructeurs - destructeur
    PrivateIndividual();
    PrivateIndividual(const string accountID, const int privilege, const list<string>& sensorID, float points);

    ~PrivateIndividual();


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    list<string> sensorID;
    float points;
};

//-------------------------------- Autres définitions dépendantes de <Attribute>

#endif // PRIVATEINDIVIDUAL_H

