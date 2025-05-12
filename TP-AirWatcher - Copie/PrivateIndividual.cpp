/*************************************************************************
                           PrivateIndividual  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <PrivateIndividual> (fichier PrivateIndividual.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "PrivateIndividual.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

list<string> PrivateIndividual::getSensorID() const
{
    return sensorID;
}

float PrivateIndividual::getPoints() const
{
    return points;
}

void PrivateIndividual::setSensorID(const list<string>& sensorID)
{
    this->sensorID = sensorID;
}

void PrivateIndividual::setPoints(float points)
{
    this->points = points;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

PrivateIndividual::PrivateIndividual()
{
}

PrivateIndividual::PrivateIndividual(const string userID, const int privilege, const list<string>& sensorID, float points)
    : User(userID, privilege), sensorID(sensorID), points(points)
{
}

PrivateIndividual::~PrivateIndividual()
{
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

