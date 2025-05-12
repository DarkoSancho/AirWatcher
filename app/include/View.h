//---------- Interface de la classe <Controller> (fichier View.h) ----------------

#if ! defined ( VIEW_H )
#define VIEW_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include <ctime>
#include <map>
#include <vector> 
using namespace std;

#include "Model.h"
#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Provider.h"
#include "Cleaner.h"
#include "User.h"
#include "View.h"
#include <ctime>
//------------------------------------------------------------------------

class View
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
   bool selectFunctionality (int option) ; 
   void mainLoop () ; 
    

//-------------------------------------------- Constructeurs - destructeur
    View ( );

    virtual ~View ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    Model model ; 
     


//----------------------------------------------------- Attributs protégés


};

//-------------------------------- Autres définitions dépendantes de <View>

#endif // VIEW_H;