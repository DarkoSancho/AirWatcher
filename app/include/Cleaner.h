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
#include "Date.h"
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Cleaner>
// Permet d'instancier des objets-métiers de classe Cleaner
//
//------------------------------------------------------------------------

class Cleaner
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

// getters 
    string getCleanerId() const;
    float getLatitude() const;
    float getLongitude() const;
    Date getStartTime() const;
    Date getEndTime() const;

    //setters 
    void setCleanerId(const string cleanerId);
    void setLatitude(const float latitude);    
    void setLongitude(const float longitude);    
    void setStartTime(const Date startTime);    
    void setEndTime(const Date endTime);

    
    // méthode qui indique si un cleaner était actif à un instant "time" donné 
    bool isActiveAt(Date time) ; 
    


//-------------------------------------------- Constructeurs - destructeur
    Cleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Cleaner (string cleanerId, float latitude, float longitude, Date startTime, Date endTime);
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
    Date startTime;
    Date endTime;
};

//-------------------------------- Autres définitions dépendantes de <Cleaner>

#endif // CLEANER_H