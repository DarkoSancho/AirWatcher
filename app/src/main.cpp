#include <iostream>
#include <map>
#include <string>
#include "Model.h"
#include "Controller.h"
#include "View.h"

using namespace std;

/*
int test () {
    Model model; // Appel au constructeur, les fichiers CSV sont chargés ici car le constructeur de model inclut le chargement

    // Test 1 : Vérifier si les capteurs sont bien chargés depuis le fichier CSV "Sensors"
    map<string, Sensor> sensors = model.getAllSensors();
    cout << "Nombre de capteurs charges : " << sensors.size() << endl;

    int count = 0;
    for (map<string, Sensor>::iterator it = sensors.begin(); it != sensors.end(); ++it)
    {
        cout << "Capteur ID : " << it->first
             << " | Latitude : " << it->second.getLatitude()
             << " | Longitude : " << it->second.getLongitude() << endl;
        if (++count >= 10) 
        break;
    }

    // Test 2 : vérifier si les utilisateurs sont chargés
    vector<User> users = model.getAllUsers();
    cout << "\nNombre d'utilisateurs charges : " << users.size() << endl;

    count = 0;
    for (vector<User>::iterator it = users.begin(); it != users.end(); ++it)
    {
        cout << "Utilisateur ID : " << it->getUserID() << endl;
        if (++count >= 5) break;
    }

    // Test 3 : Vérifier si les Mesures sont chargés 
    cout << "\nTest de recuperation des mesures pour un capteur donne" << endl;
    if (!sensors.empty())
    {
        string testSensorId = sensors.begin()->first;
        vector<Measurement> measurements = model.getMeasurements(testSensorId, "O3", 5); // Exemple : "O3"
        cout << "Nombre de mesures recuperees pour le capteur " << testSensorId << " : " << measurements.size() << endl;

        for (vector<Measurement>::iterator it = measurements.begin(); it != measurements.end(); ++it)
        {
            cout << "Timestamp : " << it->getTimestamp()
                 << " | Attribut : " << it->getAttributeId()
                 << " | Valeur : " << it->getValue() << endl;
        }
    }
    else
    {
        cout << "Aucun capteur disponible pour tester les mesures." << endl;
    }

    // Test 4 : Vérifier si les Attributs
    cout << "\nTest acces aux attributs charges (via un capteur avec mesures)" << endl;
    map<string, Attribute> attributes;
    // comme le map attributes est protected, on ne peut pas y accéder directement
    // on les récupère depuis les mesures
    if (!sensors.empty())
    {
        string testSensorId = sensors.begin()->first; // je prends le 1er sensor
        vector<Measurement> measurements = model.getMeasurements(testSensorId, "O3", 3);
        if (!measurements.empty())
        {
            string attr = measurements[0].getAttributeId();
            cout << "Exemple d'attribut mesure : " << attr << endl;
        }
        else
        {
            cout << "Aucune mesure trouvee pour tester les attributs." << endl;
        }
    }

    // test pour moi même : (ne pas oublier de l'enlever )
    // --> Objectif : comprendre comment fonctionne le type "time_t"

    time_t now = time(0);  // Obtenir l'heure actuelle
    cout << "Timestamp actuel : " << now << endl;
    
    // Convertir en format lisible
    cout << "Date/heure locale : " << ctime(&now);

    return 0;
}
*/
int main()
{
     cout << "Welcome to AirWatcher App!" << endl;

    Controller controller;
    bool isAuthenticated = false;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Sign In" << endl;
        cout << "2. Exit" << endl;
        cout << "Select your choice: "<<endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                {
                    if (isAuthenticated) {
                        cout << "You are already signed in!" << endl;
                    } else {
                        string userKey;
                        cout << "Enter user login: "<<endl;
                        cin >> userKey;
                        isAuthenticated = controller.signInUser(userKey);
                    }

                    if (isAuthenticated) {
                        controller.mainLoop();
                        isAuthenticated = false; // When view gives control back, it means user has signed out
                    }
                }
                break;
            case 2:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "You selected and invalid choice number. Please try again." << endl;
                break;
        }
    }

    return 0;
}
