/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Measurement> (fichier Measurement.h) ----------------

#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <ctime>

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Measurement>
//
//
//------------------------------------------------------------------------

class Measurement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    time_t getTimestamp() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getSensorId() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getAttributeId() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    float getValue() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setTimestamp(time_t timestamp);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setSensorId(string sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setAttributeId(string attributeId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setValue(float value);
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Measurement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Measurement ( const time_t timestamp, const string sensorId, const string attributeId, const float value);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Measurement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
time_t timestamp; 
string sensorID;
string attributeID;
float value;
};

//-------------------------------- Autres définitions dépendantes de <Measurement>

#endif //MEASUREMENT_H