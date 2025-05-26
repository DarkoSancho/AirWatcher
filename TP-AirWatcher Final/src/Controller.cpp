/*************************************************************************
                           Controller  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Controller> (fichier Controller.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cerrno>
#include <time.h>
#include <string.h>
#include <iomanip>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
//------------------------------------------------------ Include personnel
#include "Model.h"
#include "PrivateIndividual.h"
#include "Controller.h"
#include "Date.h"


// Fonctions utilitaires


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

using namespace std;

//----------------------------------------------------- Méthodes publiques
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Controller::Controller ( )
// // Algorithme :

{
     #ifdef MAP
        cout << "Appel au constructeur de <Controller>" << endl;
     #endif
}

Controller::~Controller ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au destructeur de <Controller>" << endl;
    #endif
}


// boucle principale 
void Controller :: mainLoop () {
    view.printMessage(" Welcome to AirWatcher ! Let's get started.") ; 
    string userMenu = loadMenu() ; 

    while(1) {
        cout << userMenu ; 
        int functionality ; 
        cin >> functionality ; 
        bool signOut = selectFunctionality(functionality) ; 
        if(signOut) {
            break ; 
        }
    }
}


// vérifie que l'utilisateur entre un login valide et renvoie true, si la connexion réussie 
bool Controller :: signInUser (string key ) {

    bool connexionReussie = true ; 

    if (key == "government") {
        user = User("government", 3) ; 
        return connexionReussie ; 
    }

    // cas où la personne qui se connecte n'est pas l'agence gouvernementale
    User utilisateur = model.GetUser(key) ;  // on le récupère depuis la map des Users
    if(!utilisateur.isNull()) {
        user = utilisateur ; 
        return connexionReussie ; 
    }

    view.printMessageErreur("You entered invalid user name.") ; 
    connexionReussie = false ; 
    return connexionReussie ; 

}

void Controller :: signOutUser () {
    user.~User() ; // on détruit le user qui s'était connecté pour que l'appli puisse tourner en continue 
}

bool Controller :: selectFunctionality (int functionality) {

    bool functionalitySelected = false ; 

    // on va distinguer plusieurs cas selon le privilege du user qui se connecte 
    int privilegeUser = user.getPrivilege() ; 
    switch (privilegeUser) {
        //case 0 :   // adminstrateur de l'application 
        

        case 1 : // PrivateIndividual 
        switch(functionality) {
             case 1: {
                    // Show all the sensor readings for a specific attribute 
                    view.printMessage("Showing all the readings of a Sensor");
                    
                    string sensorId = view.getStringInput("Enter Sensor ID (in the format SensorXX): ");
                    if (model.getSensor(sensorId).getSensorId() == "") {
                        view.printMessageErreur("The sensor you selected is not found");
                        break;
                    }

                    string attribute = view.getStringInput("Enter Attribute between NO2, PM10, SO2, O3 : ");

                    if (attribute != "NO2" && attribute != "PM10" && attribute != "SO2" && attribute != "O3") {
                        view.printMessageErreur("You entered an invalid Attribute");
                        break;
                    }

                    string startInput = view.getStringInput("Enter Start Date in format YYYY-MM-DD : ") ; 
                    Date startDate =  Date(startInput) ; 
                    string endInput = view.getStringInput("Enter End Date in format YYYY-MM-DD : ") ; 
                    Date endDate =  Date(endInput) ; 


                    // saisi des seuils définis par l'utilisateur 

                    //vector<Measurement> measurements = model.getMeasurements(sensorId, 10, attribute);
                    //view.displayMeasurements(measurements);

                    Stats s = model.getData(sensorId, startDate, endDate) ; 
                    view.afficherStats(s) ; 
                    break; 
                }
            case 2 : // privateIndividual
            {
                view.printSignOutConfirmation() ;
                signOutUser () ; 
                functionalitySelected = true ; 
                return functionalitySelected ; 
            }
                break ; 
            default : 
                view.printMessageErreur("You selected an invalid functionality number. Try again.") ;
                break;
        }
            break ; 

        case 2 : // AirCleaner Provider 
        switch(functionality) {
             case 1: {
                    // Show all the sensor readings for a specific attribute 
                    view.printMessage("Showing all the readings of a Sensor");
                    
                    string sensorId = view.getStringInput("Enter Sensor ID (in the format SensorXX): ");
                    if (model.getSensor(sensorId).getSensorId() == "") {
                        view.printMessageErreur("The sensor you selected is not found");
                        break;
                    }

                    string attribute = view.getStringInput("Enter Attribute between NO2, PM10, SO2, O3 : ");

                    if (attribute != "NO2" && attribute != "PM10" && attribute != "SO2" && attribute != "O3") {
                        view.printMessageErreur("You entered an invalid Attribute");
                        break;
                    }

                    string startInput = view.getStringInput("Enter Start Date in format YYYY-MM-DD : ") ; 
                    Date startDate =  Date(startInput) ; 
                    string endInput = view.getStringInput("Enter End Date in format YYYY-MM-DD : ") ; 
                    Date endDate =  Date(endInput) ; 


                    // saisi des seuils définis par l'utilisateur 

                    //vector<Measurement> measurements = model.getMeasurements(sensorId, 10, attribute);
                    //view.displayMeasurements(measurements);

                    Stats s = model.getData(sensorId, startDate, endDate) ; 
                    view.afficherStats(s) ; 
                    break; 
                }
            case 2 : // signOut
            {
                 
                view.printSignOutConfirmation() ; 
                signOutUser () ; 
                functionalitySelected = true ; 
                return functionalitySelected ; 
            }
                break ; 
            default : 
                view.printMessage("You selected an invalid functionality number. Please try again.");
                break ; 
        }
            break ; 

        case 3 : // Government Agency 
            switch(functionality) {
                case 1 : {// Mean Air quality over area : méthode Ines 

                
                view.printMessage("Mean air quality over area") ; 
                
                float lat = view.getFloatInput("Enter Latitude value : ") ; 

                // la latitude doit être comprise entre -90 et 90
                if (lat < -90 || lat > 90) {
                    view.printMessageErreur("You entered an invalid latitude value.") ; 
                    break; 
                }

                float longitude = view.getFloatInput("Enter Longitude: ");
                    
                    if (longitude < -180 || longitude > 180) {
                        view.printMessageErreur("You entered an invalid longitude value.");
                        break;
                    }

                float radius = view.getFloatInput("Enter Radius value : ") ; 

                // cas où le rayon saisi est <0
                if (radius <0 ) {
                    view.printMessageErreur("You entered an invalid radius value.") ; 
                    break ; 
                }

                string startInput = view.getStringInput("Enter Start Date in format YYYY-MM-DD : ") ; 
                Date startDate =  Date(startInput) ; 
                string endInput = view.getStringInput("Enter End Date in format YYYY-MM-DD : ") ; 
                Date endDate =  Date(endInput) ; 

                time_point<high_resolution_clock> start = high_resolution_clock::now();
                vector<float> mean = model.airQualityGeo(lat, longitude, startDate, endDate, radius); // à poursuivre quand j'aurais les méthodes des autres 
                time_point<high_resolution_clock> end = high_resolution_clock::now();
                long long time = duration_cast<milliseconds>(end - start).count();

                if (mean.size() == 0) {
                        view.printMessageErreur("There was no data available to calculate the air quality.");
                        break;
                }
                view.displayMeanAirQuality(mean);
                view.printMessage("Execution Time : " + to_string(time) + " ms.");
                break;                
            }

            // toutes les mesures pour un capteur et un attribut donné
            case 2: {
                    // Show all the sensor readings for a specific attribute 
                    view.printMessage("Showing all the readings of a Sensor");
                    
                    string sensorId = view.getStringInput("Enter Sensor ID (in the format SensorXX): ");
                    if (model.getSensor(sensorId).getSensorId() == "") {
                        view.printMessageErreur("The sensor you selected is not found");
                        break;
                    }

                    string attribute = view.getStringInput("Enter Attribute between NO2, PM10, SO2, O3 : ");

                    if (attribute != "NO2" && attribute != "PM10" && attribute != "SO2" && attribute != "O3") {
                        view.printMessageErreur("You entered an invalid Attribute");
                        break;
                    }

                    string startInput = view.getStringInput("Enter Start Date in format YYYY-MM-DD : ") ; 
                    Date startDate =  Date(startInput) ; 
                    string endInput = view.getStringInput("Enter End Date in format YYYY-MM-DD : ") ; 
                    Date endDate =  Date(endInput) ; 


                    // saisi des seuils définis par l'utilisateur 

                    //vector<Measurement> measurements = model.getMeasurements(sensorId, 10, attribute);
                    //view.displayMeasurements(measurements);
                    
                    time_point<high_resolution_clock> start = high_resolution_clock::now();
                    Stats s = model.getData(sensorId, startDate, endDate) ;  
                    time_point<high_resolution_clock> end = high_resolution_clock::now();
                    long long time = duration_cast<milliseconds>(end - start).count();
                    
                    view.afficherStats(s) ; 
                    view.printMessage("Execution Time : " + to_string(time) + " ms.");

                    break; 
                }

                case 3: {
                    // Rank and score  sensors by similarity
                    view.printMessage("Ranking sensors by similarity");

                    string sensorId = view.getStringInput("Enter the reference Sensor ID: ");
                    Sensor referenceSensor = model.getSensor(sensorId);


                    if (referenceSensor.getSensorId() == "") {
                        view.printMessageErreur("Sensor not found");
                        break;
                    }

               

                    string startInput = view.getStringInput("Enter Start Date in format YYYY-MM-DD  : ") ; // ici mettre des tirets 
                    Date startDate =  Date(startInput) ; 
                    string endInput = view.getStringInput("Enter End Date in format YYYY-MM-DD : ") ; 
                    Date endDate =  Date(endInput) ; 

                    
                    //vector<pair<string, double>> results = model.compareSensors(sensorId,10, "O3") ; 
                    time_point<high_resolution_clock> start = high_resolution_clock::now();
                    vector<pair<string, double>> results = model.compareSensors(sensorId , startDate,  endDate) ; 
                    time_point<high_resolution_clock> end = high_resolution_clock::now();
                    long long time = duration_cast<milliseconds>(end - start).count();

                    map<string, Sensor> allSensors = model.getAllSensors();
                    int numberOfSensorsCompared = allSensors.size()-1;


                    
                    //view.displayScoreAndRank(results);

                    // version de Yassine : 
                    view.displaySensorSimilarityResults(results) ; 
                    view.printMessage("Execution Time : " + to_string(time) + " ms - Compared with: " + to_string(numberOfSensorsCompared) + " sensors.");

                    break;
                }
                case 4 : {
                      int choice = view.displayPerformanceTestMenu();

                        switch (choice) {
                            case 1:
                                runTest_AverageCalculation();
                                break;
                            case 2:
                                runTest_SensorComparison();
                                break;
                            case 3:
                                runTestSensorReadings();
                                break;
                            case 4:
                                runTest_AverageCalculation();
                                runTest_SensorComparison();
                                runTestSensorReadings();
                                break;
                            default:
                                cout << "Returning to main menu.\n";
                                break;
                        }
                        break ; 
                }
                case 5: {
                    // Sign Out
                    view.printSignOutConfirmation() ; 
                    signOutUser () ; 
                    functionalitySelected = true ; 
                    return functionalitySelected ; 
                }
                    break;
                default : 
                    view.printMessage("You selected an invalid functionality number. Please try again.");
                    break ; 
            }
            break;
        default:
            break;

    }
    return functionalitySelected ; 
}


string Controller :: menuToString (Menu menu) {
    string menuString = "\nAirWatcher App - " + menu.userMenu + "\n" +"\n";
    for (int i = 0; i < menu.functionalities.size(); i++) {
        menuString += menu.functionalities[i] ; 
        menuString += "\n"; 
    }
    menuString += "\nSelect a functionality by choosing the corresponding number : ";
    return menuString;
}


string Controller :: loadMenu() {
    string menu = ""; 
    if(user.isNull()) {
        menu = "" ; 
        return menu; 
    }

    int privilege = user.getPrivilege() ; 
    switch (privilege) {
        case 1 : 
            menu = menuToString(PrivateIndividualMenu) ;
            break ;
        case 2 : 
            menu = menuToString(ProviderMenu) ; 
            break ; 
        case 3 : 
            menu = menuToString(GovernmentAgencyMenu) ; 
            break; 
        default : 
            view.printMessageErreur("Invalid privilege")  ; 
            menu = ""; 
    }
    return menu ; 
}




// Evaluation des performances

//Teste la performance de la méthode de calcul de la qualité moyenne de l'air dans une zone géographique.
// Utilise plusieurs capteurs autour d'une position fixe avec un rayon donné, et mesure le temps d'exécution
// pour le calcul de la qualité de l'air sur une période définie.
 
// Paramètres : aucun (les capteurs, rayon et dates sont définis en dur)
// Retour : aucun (affiche les résultats via la vue)
void Controller::runTest_AverageCalculation() {
    vector<string> sensors = {"Sensor1", "Sensor8", "Sensor14"};
    Date start("2019-01-01");
    Date end("2020-01-01");

    view.printMessage(">>> TEST 1: Average calculation in a zone <<<\n");
    view.printMessage("Period: from 2019-01-01 to 2020-01-01");
    view.printMessage("Radius: 5 km");
    view.printMessage("Number of tests : " + to_string(sensors.size()));

    for (const string& sensorId : sensors) {
        long long time = measureExecutionTime([&]() {
            model.airQualityGeo(44.84, -0.57, start, end, 5.0);
        });
        view.printMessage("[" + sensorId + "], Time: " + to_string(time) + " ms");
    }

    view.printMessage(">>> FIN DU TEST 1 <<<\n\n");
}

void Controller::runTest_SensorComparison() {
    vector<string> sensors = {"Sensor3", "Sensor17", "Sensor22"};
    Date start("2019-01-01");
    Date end("2020-01-01");

    map<string, Sensor> allSensors = model.getAllSensors();
    int numberOfSensorsCompared = allSensors.size()-1;

    view.printMessage(">>> TEST 2: Sensor comparison <<<\n");
    view.printMessage("Period: from 2019-01-01 to 2020-01-01");
    view.printMessage("Number of tests : " + to_string(sensors.size()));

    for (const string& refSensor : sensors) {
        long long time = measureExecutionTime([&]() {
            vector<pair<string, double>> results = model.compareSensors(refSensor, start, end);
        });

        view.printMessage("[" + refSensor + "], Time: " + to_string(time) + " ms - Compared with: " + to_string(numberOfSensorsCompared) + " sensors.");
    }
    
    view.printMessage(">>> FIN DU TEST 2 <<<\n\n");
}

void Controller::runTestSensorReadings() {
    vector<string> sensors = {"Sensor1", "Sensor8", "Sensor14"};
    string attribute = "O3";

    view.printMessage(">>> TEST 3: Sensor readings by attribute <<<\n");
    view.printMessage("Attribute: " + attribute);
    view.printMessage("Number of tests : " + to_string(sensors.size()));

    for (const string& id : sensors) {
        int count = 0;
        long long time = measureExecutionTime([&]() {
            vector<Measurement> result = model.getMeasurements(id, -1, attribute);
            count = result.size();
        });

        view.printMessage("[" + id + "], Time: " + to_string(time) + " ms - Measurements: " + to_string(count));
    }
    
    view.printMessage(">>> FIN DU TEST 3 <<<\n\n");
}
