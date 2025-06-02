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
   bool selectFunctionality (int functionality) ; 

    /**
     * @brief Boucle principale de l'application.
     * 
     * @details
     * Cette méthode contrôle le cycle de vie principal de l'application.
     * Elle gère l'affichage des menus, la saisie des utilisateurs, l'exécution des actions
     * associées aux choix utilisateurs, ainsi que les éventuels retours ou navigations.
     * 
     * La méthode ne prend aucun paramètre et ne retourne rien ; elle maintient l'application active
     * tant qu'un état de sortie n'est pas atteint (par exemple, fermeture de session ou commande "quitter").
     */
   void mainLoop () ; 


    /**
     * @brief Authentifie un utilisateur à partir d'une clé d'identification.
     * 
     * @param key Clé d'identification unique associée à un utilisateur (ex : token, identifiant chiffré).
     * @return true Si l'utilisateur est authentifié avec succès.
     * @return false Si la clé est invalide ou que l'authentification échoue.
     * 
     * @details
     * Cette méthode permet de valider l'accès d'un utilisateur en vérifiant la clé fournie.
     * Une fois connecté, l'utilisateur peut accéder aux fonctionnalités restreintes de l'application.
     * En cas d’échec, l’application peut afficher un message d’erreur ou demander une nouvelle saisie.
     */
    bool signInUser (string key ) ;



    /**
     * @brief Déconnecte l'utilisateur actuellement authentifié.
     * 
     * @details
     * Cette méthode met fin à la session de l'utilisateur connecté,
     * réinitialise les données de session, et empêche tout accès aux fonctions protégées
     * jusqu’à ce qu’un nouvel utilisateur soit authentifié.
     * Elle peut également rediriger vers le menu principal ou de connexion.
     */
    void signOutUser() ;


    /**
     * @brief Convertit un objet Menu en une chaîne de caractères lisible.
     * 
     * @param menu Objet Menu représentant un ensemble d’options ou d’étapes de navigation.
     * @return string Représentation textuelle du menu, prête à être affichée à l’utilisateur.
     * 
     * @details
     * Cette méthode transforme un objet de type Menu en une version affichable,
     * généralement composée de titres, de numéros d’option, et de descriptions associées.
     * Elle est essentielle pour fournir une interface en ligne de commande claire et structurée.
     */
    string menuToString(Menu menu) ;



        /**
     * @brief Charge le menu actuel ou initial de l'application.
     * 
     * @return string Contenu textuel du menu à afficher à l'utilisateur.
     * 
     * @details
     * Cette méthode initialise ou récupère dynamiquement le contenu du menu à afficher
     * en fonction de l'état de l'application (utilisateur connecté, rôle, progression, etc.).
     * Elle est généralement appelée au début ou après chaque action utilisateur pour mettre à jour l’interface.
     */
    string loadMenu() ; 



    void runTest_AverageCalculation() ; 
    /**
     * @brief Evaluates the performance of the average air quality calculation method within a geographic area.
     * 
     * @return void This method does not return a value; results are displayed through the view.
     * 
     * @details
     * This method tests the execution time of calculating average air quality within a specified radius
     * around a fixed geographic position using multiple sensors.
     * 
     * The test is performed over a predefined time period using hardcoded parameters:
     *   - Sensor positions
     *   - Geographic radius
     *   - Start and end dates
     * 
     * The purpose is to assess the efficiency and speed of the air quality computation algorithm.
     * Results (e.g., duration, ...) are printed or displayed via the application’s view component.
    */

    void runTest_SensorComparison() ; 
    /**
     * @brief Evaluates the performance of the sensor comparison algorithm.
     * 
     * @return void This method does not return a value; results are displayed through the view.
     * 
     * @details
     * This method tests the execution time of the algorithm that compares sensors based on their measurements.
     * 
     * For a predefined list of reference sensors, each sensor is compared to all other sensors
     * over a fixed time period. The goal is to assess the efficiency of the comparison process.
     * 
     * The test uses hardcoded parameters:
     *   - List of reference sensors
     *   - Start and end dates for the comparison period
     * 
     * Results such as execution time are displayed via the application’s view component.
    */

    void runTestSensorReadings() ; 
    /**
     * @brief Evaluates the performance of retrieving statistical data for multiple sensors over a fixed period.
     * 
     * @return void This method does not return a value; results are displayed through the view.
     * 
     * @details
     * This method measures the execution time required to compute air quality statistics
     * for a predefined list of sensors using the `getData` method from the model.
     * 
     * For each sensor:
     *   - Measurements are retrieved and analyzed over a fixed time period (from 2019-01-01 to 2020-01-01).
     *   - Thresholds for all pollutants (O3, NO2, SO2, PM10) are set to 50.
     *   - The execution time for computing the statistics is recorded and displayed.
     * 
     * The following are hardcoded:
     *   - Sensor IDs: {"Sensor1", "Sensor8", "Sensor14"}
     *   - Time period: from 2019-01-01 to 2020-01-01
     *   - Thresholds: 50 for all pollutants
     * 
     * Results (sensor ID and execution time in milliseconds) are printed via the view.
    */
    
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

    
    Menu ProviderMenu = {
        "Air Cleaner Provider Menu " , 
        {
            "1) - Show statistics for a specific sensor. ",
            "2) - Sign Out."
        }
    };

  

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
