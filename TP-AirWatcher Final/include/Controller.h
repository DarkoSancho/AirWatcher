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
#include "View.h"
#include <ctime>

#include <chrono>
using namespace std::chrono;


//------------------------------------------------------------------------

typedef struct {
    string userMenu ; 
    vector<string> functionalities ; 
} Menu ; 

class Controller
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
   bool selectFunctionality (int functionality) ; // fait 
   void mainLoop () ; 
   // authentification ? 
    bool signInUser (string key ) ; // fait  
    void signOutUser() ;  // fait
    string menuToString(Menu menu) ; // fait 
    string loadMenu() ;  // fait 
    void runTest_AverageCalculation() ; 
    void runTest_SensorComparison() ; 
    void runTestSensorReadings() ; 

    
template<typename Func>
long long measureExecutionTime(Func functionToTest) {
    time_point<high_resolution_clock> start = high_resolution_clock::now();
    functionToTest();  // appel de la fonction cible
    time_point<high_resolution_clock> end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

//-------------------------------------------- Constructeurs - destructeur
    Controller ( );
    virtual ~Controller ( );


//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Attributs protégés
    Model model ;
    View view ; 
    User user ; 
    
    Menu GovernmentAgencyMenu = {
        "Government Agency Menu " , 
        {
            "1) - Calculate mean air quality over area.",
            "2) - Show statistics for a specific sensor. ", 
            "3) - Score and rank sensors by similarity.",
            //"3) - Display 10 most recent sensor measurements.",
            "4) - Performance tests.",
            "5) - Sign Out."
        }
    } ; 

    // vérifier quelles sont les fonctionnalités auxquelles les provider ont accés 
    Menu ProviderMenu = {
        "Air Cleaner Provider Menu " , 
        {
            "1) - Show statistics for a specific sensor. ",
            "2) - Sign Out."
        }
    };

    // vérifier quelles sont les fonctionnalités auxquelles les PrivateIndividual ont accés 

    Menu PrivateIndividualMenu = {
        "Private Individual Menu" , 
        {
            "1) - Show statistics for a specific sensor. ",
            "2) - Sign Out."
        }
    } ; 
     



};

//-------------------------------- Autres définitions dépendantes de <Controller>

#endif // CONTROLLER_H;