/*************************************************************************
                           User  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <User> (fichier User.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "User.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string User::getUserID() const
{
    return userID;
}

int User::getPrivilege() const
{
    return privilegeLevel;
}

void User::setUserID(const string userID)
{
    this->userID = userID;
}

void User::setPrivilege(const int privilege)
{
    this->privilegeLevel = privilege;
}

bool User::isNull() const
{
    return (privilegeLevel == -1 || userID == "");
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

User::User()
{
}

User::User(const string userID, const int privilege)
    : userID(userID), privilegeLevel(privilege)
{
}

User::~User()
{
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

