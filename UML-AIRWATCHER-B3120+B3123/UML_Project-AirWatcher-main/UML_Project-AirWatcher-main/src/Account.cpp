/*************************************************************************
                           Account  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Account> (fichier Account.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "Account.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string Account::getAccountID() const
{
    return accountID;
}

int Account::getPrivilege() const
{
    return privilegeLevel;
}

void Account::setAccountID(const string accountID)
{
    this->accountID = accountID;
}

void Account::setPrivilege(const int privilege)
{
    this->privilegeLevel = privilege;
}

bool Account::isNull() const
{
    return (privilegeLevel == -1 || accountID == "");
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Account::Account()
{
}

Account::Account(const string accountID, const int privilege)
    : accountID(accountID), privilegeLevel(privilege)
{
}

Account::~Account()
{
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

