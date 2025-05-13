/*************************************************************************
                           Date  -  Crée une classe date 
                             -------------------
    début                : 12/05/2025
    copyright            : (C) 2025 par INSA
    e-mail               : example@insa.fr
*************************************************************************/

//---------- Réalisation de la classe <Date> (fichier Date.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
//------------------------------------------------------ Include personnel
#include "Date.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Date::Afficher() const
{
    cout << setfill('0') << setw(2) << jour << "/"
         << setw(2) << mois << "/"
         << setw(4) << annee << " "
         << setw(2) << heure << ":"
         << setw(2) << minute << ":"
         << setw(2) << seconde;
}


int Date::getYear(){
    return annee;
}


int Date::getMonth(){
    return mois;
}

int Date::getDay(){
    return jour;
}

int Date::getHour(){
    return heure;
}

int Date::getMinute(){
    return minute;
}

int Date::getSecond(){
    return seconde;
}

void Date::setYear(int uneAnnee)
{
    annee = uneAnnee;
}

void Date::setMonth(int unMois)
{
    mois = unMois;
}

void Date::setDay(int unJour){
    jour = unJour;
}

void Date::setHour(int unHeure){
    heure = unHeure;
}

void Date::setMinute(int unMinutes){
    minute = unMinutes;
}

void Date::setSecond(int unSeconde){
    seconde = unSeconde;
}

//------------------------------------------------- Surcharge d'opérateurs
Date & Date::operator = ( const Date & uneDate )
{
    if ( this != &uneDate )
    {
        jour = uneDate.jour;
        mois = uneDate.mois;
        annee = uneDate.annee;
        heure = uneDate.heure;
        minute = uneDate.minute;
        seconde = uneDate.seconde;
    }
    return *this;
}

bool Date::operator == ( const Date & uneDate ) const
{
    return jour == uneDate.jour &&
           mois == uneDate.mois &&
           annee == uneDate.annee &&
           heure == uneDate.heure &&
           minute == uneDate.minute &&
           seconde == uneDate.seconde;
}

bool Date::operator != ( const Date & uneDate ) const
{
    return !( *this == uneDate );
}

bool Date::operator < ( const Date & uneDate ) const
{
    if (annee != uneDate.annee) {
        return annee < uneDate.annee;
    }
    if (mois  != uneDate.mois){  
        return mois   < uneDate.mois;
    }
    if (jour  != uneDate.jour){  
        return jour   < uneDate.jour;
    }
    if (heure != uneDate.heure){ 
        return heure  < uneDate.heure;
    }
    if (minute != uneDate.minute) {
        return minute < uneDate.minute;
    }
    return seconde < uneDate.seconde;
}

bool Date::operator <= ( const Date & uneDate) const{
    return !(uneDate < *this);
}

bool Date::operator > ( const Date & uneDate) const{
    return uneDate>*this;
}

bool Date::operator >= ( const Date & uneDate) const{
    return !(*this < uneDate);
}

ostream & operator << ( ostream & os, const Date & date )
{
    os << std::setfill('0') << std::setw(2) << date.jour << "/"
       << std::setfill('0') << std::setw(2) << date.mois << "/"
       << std::setfill('0') << std::setw(4) << date.annee << " "
       << std::setfill('0') << std::setw(2) << date.heure << ":"
       << std::setfill('0') << std::setw(2) << date.minute << ":"
       << std::setfill('0') << std::setw(2) << date.seconde;
    return os;
}


//-------------------------------------------- Constructeurs - destructeur
Date::Date ( const Date & uneDate )
    : jour(uneDate.jour), mois(uneDate.mois), annee(uneDate.annee),
      heure(uneDate.heure), minute(uneDate.minute), seconde(uneDate.seconde)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Date>" << endl;
#endif
}


Date::Date ( int jj, int mm, int aaaa, int h, int m, int s )
    : jour(jj), mois(mm), annee(aaaa), heure(h), minute(m), seconde(s)
{
#ifdef MAP
    cout << "Appel au constructeur paramétré de <Date>" << endl;
#endif
}



Date::Date(std::string Sdate)
// Exemple attendu : "2025-05-12 10:25:30"
{
#ifdef MAP
    cout << "Appel au constructeur depuis string de <Date>" << endl;
#endif

    // Découper en deux parties : date et heure
    size_t posEspace = Sdate.find(' ');
    std::string datePart = Sdate.substr(0, posEspace);
    std::string timePart = Sdate.substr(posEspace + 1);

    // Extraction de la date : yyyy-mm-dd
    size_t pos1 = datePart.find('-');
    size_t pos2 = datePart.find('-', pos1 + 1);

    annee = std::stoi(datePart.substr(0, pos1));
    mois = std::stoi(datePart.substr(pos1 + 1, pos2 - pos1 - 1));
    jour = std::stoi(datePart.substr(pos2 + 1));

    // Extraction de l’heure : hh:mm:ss
    pos1 = timePart.find(':');
    pos2 = timePart.find(':', pos1 + 1);

    heure = std::stoi(timePart.substr(0, pos1));
    minute = std::stoi(timePart.substr(pos1 + 1, pos2 - pos1 - 1));
    seconde = std::stoi(timePart.substr(pos2 + 1));
}




Date::Date ( )
    : jour(1), mois(1), annee(1970), heure(0), minute(0), seconde(0)
{
#ifdef MAP
    cout << "Appel au constructeur par défaut de <Date>" << endl;
#endif
}

Date::~Date ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Date>" << endl;
#endif
}
