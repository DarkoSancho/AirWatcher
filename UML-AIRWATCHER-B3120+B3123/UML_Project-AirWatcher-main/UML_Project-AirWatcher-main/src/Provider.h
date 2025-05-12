/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#ifndef PROVIDER_H
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include "Account.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Provider>
//
//
//------------------------------------------------------------------------

class Provider : public Account
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    // Getter
    list<string> getCleanerID() const;

    // Setter
    void setCleanerID(const list<string>& cleanerID);


//-------------------------------------------- Constructeurs - destructeur
    Provider();
    Provider(const string accountID, const int privilege, const list<string>& cleanerID);

    ~Provider();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    list<string> cleanerID;
};

#endif // PROVIDER_H

