/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Measurement> (fichier Measurement.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string Measurement::getTimestamp() const
{
    return timestamp;
}

string Measurement::getSensorId() const
{
    return sensorID;
}

string Measurement::getAttributeId() const
{
    return attributeID;
}

float Measurement::getValue() const
{
    return value;
}

void Measurement::setTimestamp(string timestamp)
{
    this->timestamp = timestamp;
}

void Measurement::setSensorId(string sensorId)
{
    this->sensorID = sensorId;
}

void Measurement::setAttributeId(string attributeId)
{
    this->attributeID = attributeId;
}

void Measurement::setValue(float value)
{
    this->value = value;
}

//-------------------------------------------- Constructeurs - destructeur

Measurement::Measurement()
{
    // Constructeur par défaut
}

Measurement::Measurement(const string timestamp, const string sensorId, const string attributeId, const float value)
    : timestamp(timestamp), sensorID(sensorId), attributeID(attributeId), value(value)
{
}


Measurement::~Measurement()
{
    // Destructeur
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Méthodes protégées
