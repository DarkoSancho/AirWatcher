/*************************************************************************
                           View  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <View> (fichier View.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream> 

//------------------------------------------------------ Include personnel
#include "Model.h"
#include "Controller.h"
#include "View.h"
#include "Date.h"


void View::printMessage(string line){
    cout << "AirWatcher App - " << line << endl;
}

void View::printMessageErreur(const string message) {
    cerr << "\nAirWatcher App - Error: " << message << endl;
}


void View::printSignInConfirmation(bool SignedIn) {
    if (SignedIn) {
        cout << "\nAirWatcher App - You signed in succesfully. Let's get started with the AirWatcher App!" << endl;
    } else {
        cerr << "\nAirWatcher App - Sign-in failed. An error occured. Please try again." << endl;
    }
}

void View::printSignOutConfirmation() {
    cout << "\nAirWatcher App- You signed out successfully !" << endl;

}

void View::displayMeanAirQuality(vector<float> meanAirQuality){
    cout << "\nAirWatcher App - Mean air quality over the selected area : " << endl; 
    cout << "Attribute" << " || " << "Mean value" << endl;
    cout << "NO2      " << " || " << meanAirQuality[0] << endl;
    cout << "O3       " << " || " << meanAirQuality[1] << endl;
    cout << "PM10     " << " || " << meanAirQuality[3] << endl;
    cout << "SO2      " << " || " << meanAirQuality[2] << endl;
}



void View::displayScoreAndRank(const vector<pair<string, double>>& rankingVector) {
    cout << "\nAirWatcher App - Sensor ranking by similarity to given reference (higher is more similar)" << endl; 
    cout << "Rank" << " || " << "Sensor ID" << " || " << "Similarity score" << endl;

    int rank = 1;
    for (size_t i = 0; i < rankingVector.size(); ++i) {
        cout << rank << " || " << rankingVector[i].first << " || " << rankingVector[i].second << endl;
        rank++;
    }
}

// méthode de Yassine
void View::displaySensorSimilarityResults(const vector<pair<string, double>>& results) {
    cout << "\n==== RESULTS ====\n" << endl;
    
    int rank = 1;
    for (const auto& pair : results) {
        cout << "Rank : " << rank++ << ", SensorId : " << pair.first << ", Similarity Score : " << pair.second << endl;
    }
}




void View::displayMeasurements(vector<Measurement> measurements){
    cout << "AirWatcher App - Displaying 10 most recent sensor readings" << endl;
    cout << "Sensor ID" << " || " << "Attribute" << " | " << "Value" << " | " << "Timestamp" << endl;
    for (Measurement m : measurements){
        cout << m.getSensorId() << " || " << m.getAttributeId() << " || " << m.getValue() << " | " << m.getTimestamp() << endl;
    }
}

int View::getIntInput(string userInput){
    cout << userInput<<endl;
    int value;
    cin >> value;
    return value;
}
// Ajout d'un saut de ligne après chaque cin pour plus de clarté
// (déjà fait dans getIntInput)
// À ajouter dans getFloatInput et getStringInput

float View::getFloatInput(string userInput){
cout << userInput<<endl;
float value;
cin >> value;
return value;
}

string View::getStringInput(string userInput){
cout << userInput<<endl;
string value;
cin >> value;
return value;
}




// méthode de Tom 

void View :: afficherStats(const Stats& S) {
    cout << "---- Averages ----" << endl;
    for (const auto& pair : S.average) {
        if (pair.second == -1) {
            cout << pair.first << " : no data" << endl;
        } else {
            cout << pair.first << " : " << pair.second << endl;
        }
    }
    cout << "---- Minimum ----" << endl;
    for (const auto& pair : S.minimum) {
        if (pair.second == -1) {
            cout << pair.first << " : no data" << endl;
        } else {
            cout << pair.first << " : " << pair.second << endl;
        }
    }
    cout << "---- Maximum ----" << endl;
    for (const auto& pair : S.maximum) {
        if (pair.second == -1) {
            cout << pair.first << " : no data" << endl;
        } else {
            cout << pair.first << " : " << pair.second << endl;
        }
    }
    cout << "---- Standard deviation ----" << endl;
    for (const auto& pair : S.sdeviation) {
        if (pair.second == -1) {
            cout << pair.first << " : no data / No threshold provided" << endl;
        } else {
            cout << pair.first << " : " << pair.second << endl;
        }
    }
    cout << "---- Exceedances ----" << endl;
    for (const auto& pair : S.excedances) {
        if (pair.second == -1) {
            cout << pair.first << " : no data / No threshold provided" << endl;
        } else {
            cout << pair.first << " : " << pair.second << endl;
        }
    }
    cout << "---- Date and value ATMO min ----" << endl;
    if (S.matmo.second == -1) {
        cout << S.matmo.first << " : no data" << endl;
    } else {
        cout << S.matmo.first << " : " << S.matmo.second << endl;
    }
    cout << "---- Date and value ATMO max ----" << endl;
    if (S.Matmo.second == -1) {
        cout << S.Matmo.first << " : no data" << endl;
    } else {
        cout << S.Matmo.first << " : " << S.Matmo.second << endl;
    }
    for (const auto& pair : S.average) {
        cout << pair.first << " : " << pair.second << endl;
    }
}


// tests de performance 

int View::displayPerformanceTestMenu() {
    cout << "\n===== PERFORMANCE TEST MENU =====\n\n";
    cout << "Select algorithms to test :\n";
    cout << "1. Average calculation in a zone\n";
    cout << "2. Sensor comparison\n";
    cout << "3. Sensor readings\n";
    cout << "4. All algorithms\n";
    cout << "0. Back\n";
    string input = getStringInput("Your choice: ");
    return stoi(input); 
}
