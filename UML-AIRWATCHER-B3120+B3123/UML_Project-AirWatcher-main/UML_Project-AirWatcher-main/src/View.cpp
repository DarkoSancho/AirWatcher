/*
AirWatcher - A C++ program to manage air quality monitoring stations.
View -> Command Line Interface (CLI) Main File

*/

// Directives and Libraries
#include "View.h"
#include "controller.h"
#include "Utility.h"
#include <iostream>

using namespace std;

void AirWatcherView::printError(const string message) {
    cerr << "\nAIRWATCHER - Error: " << message << endl;
}


void AirWatcherView::displaySignInResult(bool isSignedIn) {
    if (isSignedIn) {
        cout << "\nAIRWATCHER - Sign-in successful. Welcome to the system!" << endl;
    } else {
        cerr << "\nAIRWATCHER - Sign-in failed. Please check your credentials and try again." << endl;
    }
}

void AirWatcherView::displaySignOutConfirmation() {
    cout << "\nAIRWATCHER - Sign-out successful. Goodbye!" << endl;

}

void AirWatcherView::displayMeanAirQuality(vector<float> meanAirQuality){
    cout << "\nAIRWATCHER - Mean air quality over the selected area : " << endl; 
    cout << "Attribute" << " | " << "Mean" << endl;
    cout << "NO2      " << " | " << meanAirQuality[0] << endl;
    cout << "O3       " << " | " << meanAirQuality[1] << endl;
    cout << "PM10     " << " | " << meanAirQuality[3] << endl;
    cout << "SO2      " << " | " << meanAirQuality[2] << endl;
}



void AirWatcherView::displayRank(map<float, Sensor> rankMap){
    cout << "\nAIRWATCHER - Sensor ranking by similarity to given reference (less is more similar)" << endl; 
    cout << "Rank" << " | " << "Sensor ID" << " | " << "Similarity score" << endl;
    
    int rank = 1;
    for (auto it = rankMap.rbegin(); it != rankMap.rend(); it++){
        cout << rank << " | " << it->second.getSensorId() << " | " << it->first << endl;
        rank++;
    }

}

void AirWatcherView::displayMeasurements(vector<Measurement> measurements){
    cout << "\nAIRWATCHER - Displaying 10 most recent sensor readings" << endl;
    cout << "Sensor ID" << " | " << "Attribute" << " | " << "Value" << " | " << "Timestamp" << endl;
    for (Measurement m : measurements){
        cout << m.getSensorId() << " | " << m.getAttributeId() << " | " << m.getValue() << " | " << Utility::convertToString(m.getTimestamp()) << endl;
    }
}

void AirWatcherView::printLine(string line){
    cout << "AIRWATCHER - " << line << endl;
}

float AirWatcherView::getFloat(string prompt){
    cout << prompt;
    float value;
    cin >> value;
    return value;
}

string AirWatcherView::getString(string prompt){
    cout << prompt;
    string value;
    cin >> value;
    return value;
}

int AirWatcherView::getInt(string prompt){
    cout << prompt;
    int value;
    cin >> value;
    return value;
}



