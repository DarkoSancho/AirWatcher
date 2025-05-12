/*
AirWatcher - A C++ program to manage air quality monitoring stations.
Controller -> Class that manages user input received from the View

*/

/*
g++ -Wall -Wextra -c src/*.cpp
if not exist obj mkdir obj
move *.o obj/
g++ -Wall -Wextra obj/*.o -o airwatcher.exe

*/

// Directives and Libraries
#include "Controller.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Account.h"
#include <vector>
#include "Model.h"
#include "Utility.h"
using namespace std;

string menuToString(Menu menu) {
    string menuString = "\nAIRWATCHER - " + menu.title + "\n";
    for (int i = 0; i < menu.options.size(); i++) {
        menuString += menu.options[i] + "\n";
    }
    menuString += "Enter your choice: ";
    return menuString;
}

// Constructor
Controller::Controller() {
        
}
        
// Destructor
Controller::~Controller() {
    
}

string Controller::loadPrivilegedMenu() {
    if (account.isNull()) {
        view.printError("No Account Signed In");
        return "";
    }

    switch (account.getPrivilege()) {
        case 0:
            return menuToString(adminMenu);
        case 1:
            return menuToString(userMenu);
        case 2:
            return menuToString(providerMenu);
        case 3:
            return menuToString(publicInstitutionMenu);
        default:
            view.printError("Invalid Privilege Level");
            return "";
    }
}

void Controller::mainLoop(){
    view.printLine("Welcome to AirWatcher!");
    string menu = loadPrivilegedMenu();

    while (true) {
        cout << menu;
        int choice;
        cin >> choice;
        bool signedOut = selectOption(choice);
        if (signedOut) {
            break;
        }
    }
}

vector<Account> Controller::showAvailableAccounts() {
    return model.getAllAccounts();
}

bool Controller::selectOption(int option) {

    // MUST FOLLOW MENUS DEFINED IN CLASS MEMBERS

    if (account.isNull()) {
        return true;
    }

    switch (account.getPrivilege()) {
        case 0: // ADMIN
            switch (option) {
                case 4: {
                    // Sign Out
                    view.displaySignOutConfirmation();
                    signOutUser();
                    return true;
                }
                    break;
                default:
                    view.printError("Invalid Option");
                    break;
            }
            break;
        case 1: // USER
            switch (option) {
                
                case 4: {
                    // Sign Out
                    view.displaySignOutConfirmation();
                    signOutUser();
                    return true;
                }
                    break;
                default:
                    view.printError("Invalid Option");
                    break;
            }
            break;
        case 2: // PROVIDER
            switch (option) {
                case 4: {
                    // Sign Out
                    view.displaySignOutConfirmation();
                    signOutUser();
                    return true;
                }
                    break;
                default:
                    view.printError("Invalid Option");
                    break;
            }
            break;
        case 3: // PUBLIC INSTITUTION
            switch (option) {
                case 1: {
                    // Show 10 most recent sensor readings
                    view.printLine("Showing 10 most recent readings of a Sensor");
                    
                    string sensorId = view.getString("Enter Sensor ID (SensorXX): ");
                    if (model.getSensor(sensorId).getSensorId() == "") {
                        view.printError("Sensor not found");
                        break;
                    }

                    string attribute = view.getString("Enter Attribute (NO2, PM10, SO2, O3): ");

                    if (attribute != "NO2" && attribute != "PM10" && attribute != "SO2" && attribute != "O3") {
                        view.printError("Invalid Attribute");
                        break;
                    }

                    vector<Measurement> measurements = model.getMeasurements(sensorId, 10, attribute);
                    view.displayMeasurements(measurements);

                }
                    break;
                case 2: {
                
                    // Calculate mean air quality over area
                    view.printLine("Calculating mean air quality over area");

                    float latitude = view.getFloat("Enter Latitude: ");

                    if (latitude < -90 || latitude > 90) {
                        view.printError("Invalid Latitude");
                        break;
                    }

                    float longitude = view.getFloat("Enter Longitude: ");
                    
                    if (longitude < -180 || longitude > 180) {
                        view.printError("Invalid Longitude");
                        break;
                    }
                    
                    float radius = view.getFloat("Enter Radius: ");

                    if (radius < 0) {
                        view.printError("Invalid Radius");
                        break;
                    }

                    
                    string startString = view.getString("Enter Start Date (DD/MM/YYYY): ");
                    time_t start = Utility::convertToTimeT(startString);   

                    string endString = view.getString("Enter End Date (DD/MM/YYYY): ");
                    time_t end = Utility::convertToTimeT(endString);

                    vector<float> meanAirQuality = model.calculateMeanAirQuality(latitude, longitude, radius, start, end);
                    
                    if (meanAirQuality.size() == 0) {
                        view.printError("No Data Found");
                        break;
                    }

                    view.displayMeanAirQuality(meanAirQuality);

                    break;
                }
                case 3: {
                    // Rank sensors by similarity
                    view.printLine("Ranking sensors by similarity");

                    string sensorId = view.getString("Enter Sensor ID: ");
                    Sensor sensor = model.getSensor(sensorId);

                    if (sensor.getSensorId() == "") {
                        view.printError("Sensor not found");
                        break;
                    }

                    string attribute = view.getString("Enter Attribute (NO2, PM10, SO2, O3): ");

                    if (attribute != "NO2" && attribute != "PM10" && attribute != "SO2" && attribute != "O3") {
                        view.printError("Invalid Attribute");
                        break;
                    }

                    int resultCount = view.getInt("Enter Number of Results: ");

                    if (resultCount < 1) {
                        view.printError("Invalid Result Count");
                        break;
                    }

                    map<float, Sensor> results = model.scoreAndRankSensors(sensor, resultCount, attribute);
                    view.displayRank(results);

                    break;
                }
                case 4: {
                    // Sign Out
                    view.displaySignOutConfirmation();
                    signOutUser();
                    return true;
                }
                    break;
                default:
                    view.printError("Invalid Option");
                    break;
            }
            break;
        default:
            break;
    }

    return false;
}

// Public Member Functions
bool Controller::attemptSignInUser(string key) {
    
    if (key == "admin") {
        account = Account("admin", 0);
        return true;
    }


    if (key == "gouv") {
        account = Account("gouv", 3);
        return true;
    }

    Account ac = model.GetAccount(key);
    if (!ac.isNull()) {
        account = ac;
        return true;
    }

    view.printError("Invalid Credentials");
    return false;
}

void Controller::signOutUser() {
    account.~Account();
}


