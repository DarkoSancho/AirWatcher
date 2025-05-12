/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Cleaner> (fichier Cleaner.h) ----------------

#if ! defined ( CLEANER_H )
#define CLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <ctime>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Cleaner>
//
//
//------------------------------------------------------------------------

class Cleaner
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    string getCleanerId() const;
    float getLatitude() const;
    float getLongitude() const;
    time_t getStartTime() const;
    time_t getEndTime() const;

    void setCleanerId(const string cleanerId);
    void setLatitude(const float latitude);    
    void setLongitude(const float longitude);    
    void setStartTime(const time_t &startTime);    
    void setEndTime(const time_t &endTime);
    


//-------------------------------------------- Constructeurs - destructeur
    Cleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Cleaner (string cleanerId, float latitude, float longitude, time_t startTime, time_t endTime);
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Cleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    string cleanerId;
    float latitude;
    float longitude;
    time_t startTime;
    time_t endTime;
};

//-------------------------------- Autres définitions dépendantes de <Cleaner>

#endif // CLEANER_H