/*************************************************************************
                           Account  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Account> (fichier Account.h) ----------------
#ifndef ACCOUNT_H
#define ACCOUNT_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
enum PrivilegeLevel
{
    ADMIN = 0,
    PRIVATE_INDIVIDUAL = 1,
    PROVIDER = 2,
    PUBLIC_INSTITUTION = 3
};

//------------------------------------------------------------------------
// Rôle de la classe <Account>
//
//
//------------------------------------------------------------------------

class Account
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // Getters
    string getAccountID() const;
    int getPrivilege() const;

    // Setters
    void setAccountID(const string accountID);
    void setPrivilege(const int privilege);

    bool isNull() const;

    // Surcharge de l'opérateur <<
    friend ostream &operator<<(ostream &os, const Account &account);

//-------------------------------------------- Constructeurs - destructeur
    Account();
    Account(const string accountID, const int privilege);
    ~Account();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    string accountID;
    int privilegeLevel;


};

//-------------------------------- Autres définitions dépendantes de <Attribute>

#endif // ACCOUNT_H

