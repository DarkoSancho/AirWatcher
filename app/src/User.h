/*************************************************************************
                           User  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ----------------
#ifndef USER_H
#define USER_H

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
// Rôle de la classe <User>
//
//
//------------------------------------------------------------------------

class User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // Getters
    string getUserID() const;
    int getPrivilege() const;

    // Setters
    void setUserID(const string userID);
    void setPrivilege(const int privilege);

    bool isNull() const;

    // Surcharge de l'opérateur <<
    friend ostream &operator<<(ostream &os, const User &user);

//-------------------------------------------- Constructeurs - destructeur
    User();
    User(const string userID, const int privilege);
    ~User();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

    string userID;
    int privilegeLevel;


};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // USER_H

