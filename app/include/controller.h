//---------- Interface de la classe <Controller> (fichier Controller.h) ----------------

#if ! defined ( CONTROLLER_H )
#define CONTROLLER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include <ctime>
#include <map>
#include <vector> 
using namespace std;

#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Provider.h"
#include "Cleaner.h"
#include "User.h"
#include <ctime>
//------------------------------------------------------------------------

class Controller
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
   

//-------------------------------------------- Constructeurs - destructeur
    Controller ( );

    virtual ~Controller ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées



//----------------------------------------------------- Attributs protégés


};

//-------------------------------- Autres définitions dépendantes de <Controller>

#endif // CONTROLLER_H;