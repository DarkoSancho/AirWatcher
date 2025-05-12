/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Provider> (fichier Provider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "Provider.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

list<string> Provider::getCleanerID() const
{
    return cleanerID;
}

void Provider::setCleanerID(const list<string>& cleanerID)
{
    this->cleanerID = cleanerID;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Provider::Provider()
{
}

Provider::Provider(const string userID, const int privilege, const list<string>& cleanerID)
    : User(userID, privilege), cleanerID(cleanerID)
{
}

Provider::~Provider()
{
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

