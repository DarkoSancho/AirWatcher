/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Attribute> (fichier Attribute.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Attribute::getAttributeId()
{
    return attributeId;
}

string Attribute::getUnit()
{
    return unit;
}

string Attribute::getDescription()
{
    return description;
}

void Attribute::setAttributeId(string attributeId)
{
    this->attributeId = attributeId;
}

void Attribute::setUnit(string unit)
{
    this->unit = unit;
}

void Attribute::setDescription(string description)
{
    this->description = description;
}

//-------------------------------------------- Constructeurs - destructeur

Attribute::Attribute()
{
    // Constructeur par défaut
}

Attribute::Attribute(string attributeId, string unit, string description)
    : attributeId(attributeId), unit(unit), description(description)
{
}

Attribute::~Attribute()
{
    // Destructeur
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Méthodes protégées
