/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Attribute>
//
//
//------------------------------------------------------------------------

class Attribute
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string getAttributeId();
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getUnit();
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getDescription();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setAttributeId(string attributeId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setUnit(string unit);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setDescription(string description);
    // Mode d'emploi :
    //
    // Contrat :
    //



//-------------------------------------------- Constructeurs - destructeur
    Attribute ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Attribute ( const string attributeId, const string unit, const string description );
    // Mode d'emploi :
    //
    // Contrat :
    //
    

    virtual ~Attribute ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string attributeId; // on en 4 différents : O3, NO2, SO2, PM10
    string unit;
    string description;
};

//-------------------------------- Autres définitions dépendantes de <Attribute>

#endif // ATTRIBUTE_H

