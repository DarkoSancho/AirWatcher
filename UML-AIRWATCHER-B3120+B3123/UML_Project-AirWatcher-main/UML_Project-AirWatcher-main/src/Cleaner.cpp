/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Cleaner> (fichier Cleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Cleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// Getters
string Cleaner::getCleanerId() const
{
    return cleanerId;
}

float Cleaner::getLatitude() const
{
    return latitude;
}

float Cleaner::getLongitude() const
{
    return longitude;
}

time_t Cleaner::getStartTime() const
{
    return startTime;
}

time_t Cleaner::getEndTime() const
{
    return endTime;
}

// Setters
void Cleaner::setCleanerId(const string cleanerId)
{
    this->cleanerId = cleanerId;
}

void Cleaner::setLatitude(const float latitude)
{
    this->latitude = latitude;
}

void Cleaner::setLongitude(const float longitude)
{
    this->longitude = longitude;
}

void Cleaner::setStartTime(const time_t &startTime)
{
    this->startTime = startTime;
}

void Cleaner::setEndTime(const time_t &endTime)
{
    this->endTime = endTime;
}

//-------------------------------------------- Constructeurs - destructeur

Cleaner::Cleaner()
{
    // Constructeur par défaut
}

Cleaner::Cleaner(string cleanerId, float latitude, float longitude, time_t startTime, time_t endTime)
    : cleanerId(cleanerId), latitude(latitude), longitude(longitude), startTime(startTime), endTime(endTime)
{
    // Constructeur avec paramètres
}

Cleaner::~Cleaner()
{
    // Destructeur
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Méthodes protégées
