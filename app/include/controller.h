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

#include "Model.h"
#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Provider.h"
#include "Cleaner.h"
#include "User.h"
//#include "View.h"
#include <ctime>
//------------------------------------------------------------------------

class Controller
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
   bool selectFunctionality (int option) ; 
   void mainLoop () ; 
   // authentification ? 

    bool signInUser (string key ) ; 



//-------------------------------------------- Constructeurs - destructeur
    Controller ( );

    virtual ~Controller ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    Model model ;
    //View view ; 
    
    
     


//----------------------------------------------------- Attributs protégés


};

//-------------------------------- Autres définitions dépendantes de <Controller>

#endif // CONTROLLER_H;