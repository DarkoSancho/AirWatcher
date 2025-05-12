/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------

#if ! defined ( SENSOR_H )
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string getSensorId() const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    float getLatitude();
    // Mode d'emploi :
    //
    // Contrat :
    //

    float getLongitude();
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool getFlagged();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setSensorId(string attributeId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setLatitude(float latitude);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setLongitude(float longitude);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setFlagged(bool flagged);
    // Mode d'emploi :
    //
    // Contrat :
    //



//-------------------------------------------- Constructeurs - destructeur
    Sensor ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Sensor (const string sensorId, float latitude, float longitude, bool flagged);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string sensorId; 
float latitude;
float longitude;
bool flagged;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // SENSOR_H