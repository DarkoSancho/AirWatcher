/*************************************************************************
                           Date  -  Représente une date et une heure
                             -------------------
    début                : 12/05/2025
    copyright            : (C) 2025 par INSA
    e-mail               : example@insa.fr
*************************************************************************/

//---------- Interface de la classe <Date> (fichier Date.h) ----------------
#if ! defined ( DATE_H )
#define DATE_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Date>
//
// Représente une date et une heure (jj/mm/aaaa hh:mm:ss), avec
// surcharge des opérateurs principaux.
//
class Date 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Afficher() const;

    int getYear();
    int getMonth();
    int getDay();
    int getHour();
    int getMinute();
    int getSecond();

    void setYear(int unAnnee);
    void setMonth(int unMois);
    void setDay(int unJour);
    void setHour(int unHeure);
    void setMinute(int unMinute);
    void setSecond(int unSeconde);


//------------------------------------------------- Surcharge d'opérateurs
    Date & operator = ( const Date & uneDate );
    bool operator == ( const Date & uneDate ) const;
    bool operator != ( const Date & uneDate ) const;
    bool operator <  ( const Date & uneDate ) const;
    bool operator >  ( const Date & uneDate ) const;
    bool operator <= ( const Date & uneDate ) const;
    bool operator >= ( const Date & uneDate ) const;
    friend std::ostream & operator << ( std::ostream & os, const Date & date );

//-------------------------------------------- Constructeurs - destructeur
    Date ( const Date & uneDate );
    Date ( int jj, int mm, int aaaa, int h = 0, int m = 0, int s = 0 );
    Date(string Sdate);
    Date ( );
    virtual ~Date ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    int seconde;
};

#endif // DATE_H
