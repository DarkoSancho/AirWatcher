//---------- Interface de la classe <View> (fichier View.h) ----------------

#if ! defined ( VIEW_H )
#define VIEW_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <map>
#include <vector> 
using namespace std;

#include "Model.h"
#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"

class View {
    //----------------------------------------------------------------- PUBLIC

    public:
    //----------------------------------------------------- Méthodes publiques

    // affichage messages console
    void printMessage(string message) ; 
    void printMessageErreur (string message) ;
    void printSignInConfirmation (bool SignedIn) ; 
    void printSignOutConfirmation () ; 


    // affichage résultat des fonctionnalités de la classe Model
    void displayMeanAirQuality(vector<float> meanAirQuality) ; 
    void displayMeasurements(vector <Measurement> measurements) ; 
    //void displayScoreAndRank(map<float, Sensor> ranking) ; 
    void displaySensorSimilarityResults(const vector<pair<string, double>>& results) ;
    
    // méthode de Tom : 
    void afficherStats(const Stats& S) ; 


    void displayScoreAndRank(const vector<pair<string, double>>& rankingVector); 
    int displayPerformanceTestMenu() ; 

    int getIntInput(string userInput) ; 
    float getFloatInput(string userInput) ; 
    string getStringInput(string userInput) ; 

} ; 


#endif // VIEW_H;