#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include "Sensor.h"
#include <vector>
#include "Measurement.h"

class AirWatcherView {
public:
    
    void printError(const std::string message);
    void printLine(string line);

    void displaySignInResult(bool isSignedIn);
    void displaySignOutConfirmation();

    float getFloat(string prompt);
    int getInt(string prompt);
    string getString(string prompt);
    
    void displayRank(map<float, Sensor> rankMap);
    void displayMeanAirQuality(vector<float> meanAirQuality);
    void displayMeasurements(vector<Measurement> measurements);
};

#endif
