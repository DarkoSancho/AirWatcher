/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Sensor::getSensorId() const
{
    return sensorId;
}

float Sensor::getLatitude()
{
    return latitude;
}

float Sensor::getLongitude()
{
    return longitude;
}

bool Sensor::getFlagged()
{
    return flagged;
}

void Sensor::setSensorId(string sensorId)
{
    this->sensorId = sensorId;
}

void Sensor::setLatitude(float latitude)
{
    this->latitude = latitude;
}

void Sensor::setLongitude(float longitude)
{
    this->longitude = longitude;
}

void Sensor::setFlagged(bool flagged)
{
    this->flagged = flagged;
}

//-------------------------------------------- Constructeurs - destructeur

Sensor::Sensor()
{
    // Constructeur par défaut
}

Sensor::Sensor(const string sensorId, const float latitude, const float longitude, bool flagged)
    : sensorId(sensorId), latitude(latitude), longitude(longitude), flagged(flagged)
{
}


Sensor::~Sensor()
{
    // Destructeur
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Méthodes protégées
