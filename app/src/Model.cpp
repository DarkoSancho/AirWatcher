/*************************************************************************
                           Model  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Model> (fichier Model.cpp) ------------

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


// Fonctions utilitaires


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

using namespace std;

//----------------------------------------------------- Méthodes publiques
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Model::Model ( )
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <Model>" << endl;
    #endif

    // Load users data
    string pathUserCSV = "ressources/users.csv";
    string pathProviderCSV = "ressources/providers.csv";
    string pathCleanerCSV = "ressources/cleaners.csv";
    string pathSensorCSV = "ressources/sensors.csv";
    string pathMeasureCSV = "ressources/measurements.csv";
    string pathAttributeCSV = "ressources/attributes.csv";

    // Remplissage des données dans les différentes structures
    loadCleaners(pathCleanerCSV);
    loadSensorsData(pathSensorCSV, pathMeasureCSV, pathAttributeCSV);
    loadUsersData(pathUserCSV, pathProviderCSV);
    
} //----- Fin de Model


Model::~Model ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Model>" << endl;
#endif
} //----- Fin de ~Model


//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées


bool Model::loadUsersData(string pathUserCSV, string pathProviderCSV)
    {
        // Chargement des PrivateIndividuals
        ifstream userFile(pathUserCSV);
        if (!userFile.is_open()) {
            cerr << "Error: cannot open file " << pathUserCSV << endl;
            return false;
        }
    
        string line;  // ligne du fihcier CSV 
        while (getline(userFile, line)) { // getline lit une ligne jusqu'à ce que je rencontre un retour à la ligne
            vector<string> row;
            int pos = 0;

            // le séparateur dans nos fichiers CSV est un ";"
            while ((pos = line.find(';')) != string::npos) { // find renvoie npos quand il ne trouve pas ";"
                row.push_back(line.substr(0, pos)); // on ajoute à row le contenu de "line" jusqu'à "pos", on extrait la sous-chaîne de début jusqu’à juste avant ';' 
                line.erase(0, pos + 1); // on retire la partie de la "line" de 0 à pos, y compris le ";"
            }
            row.push_back(line); // dernier champ
    
            if (row.size() >= 2) { // on vérifie que la ligne contient au moins 2 champs 
                // j'instancie un privateIndividual
                PrivateIndividual individualUser;
                individualUser.setUserID(row[0]);
                individualUser.setPrivilege(PRIVATE_INDIVIDUAL);

                // on stocke le privateIndividual instancié dans la map "users"
                this->users[row[0]] = individualUser;
            }
        }
        userFile.close();
    
        // Chargement des providers selon la même logique que les privateIndividual
        ifstream providerFile(pathProviderCSV);
        if (!providerFile.is_open()) {
            cerr << "Error: cannot open file " << pathProviderCSV << ": " << strerror(errno) << endl;
            return false;
        }
    
        while (getline(providerFile, line)) {
            vector<string> row;
            int pos = 0;
            while ((pos = line.find(';')) != string::npos) {
                row.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            row.push_back(line);
    
            if (!row.empty()) {
                Provider provider;
                provider.setUserID(row[0]);
                provider.setPrivilege(PROVIDER);

                // on doit à présent stocker le provider créé dans 2 maps : users & providers 
                this->providers[row[0]] = provider;
                this->users[row[0]] = provider;
            }
        }
        providerFile.close();
    
        return true;
    }
    

bool Model::loadCleaners(string pathCleanerCSV)
{
    ifstream file(pathCleanerCSV);
    if (!file.is_open()) {
        cerr << "Error: cannot open file " << pathCleanerCSV << ": " << strerror(errno) << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        int pos = 0;
        while ((pos = line.find(';')) != string::npos) {
            row.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        row.push_back(line); // dernier champ

        if (row.size() >= 5) { // on vérifie que la ligne contient au moins 5 champs (ID, latitude, longitude, début, fin).
            Cleaner cleaner;
            cleaner.setCleanerId(row[0]);
            cleaner.setLatitude(stof(row[1])); // "stof" convertie une string en float
            cleaner.setLongitude(stof(row[2])); 
            cleaner.setStartTime(row[3]); // NAM : Asmae je dois changer ça
            cleaner.setEndTime(row[4]); // NAM : Asmae je dois changer ça avec la méthode date de Tom 
            this->cleaners[row[0]] = cleaner;
        }
    }

    file.close();
    return true;
}


bool Model::loadSensorsData(string pathSensorCSV, string pathMeasureCSV, string pathAttributeCSV)
{
    // Chargement des capteurs
    ifstream sensorFile(pathSensorCSV);
    if (!sensorFile.is_open()) {
        cerr << "Error: cannot open file " << pathSensorCSV << ": " << strerror(errno) << std::endl;
        return false;
    }

    string line;
    while (getline(sensorFile, line))
    {   
        vector<string> row;
        int pos = 0;
        while ((pos = line.find(';')) != string::npos) {    // find renvoie string::npos si elle ne trouve pas ce qu'elle cherche, ici ";"
            row.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        row.push_back(line); // Ajouter le dernier champ

        // Créer un objet Sensor
        Sensor sensor;
        sensor.setSensorId(row[0]);
        sensor.setLatitude(stof(row[1])); // "stof" convertie une string en float
        sensor.setLongitude(stof(row[2]));
        sensor.setFlagged(false);

        // Ajouter le capteur à la map
        this->sensors[row[0]] = sensor;
    }
    sensorFile.close();

    // Chargement des mesures
    ifstream measurementFile(pathMeasureCSV);
    if (!measurementFile.is_open()) {
        cerr << "Error: cannot open file " << pathMeasureCSV << ": " << strerror(errno) << std::endl;
        return false;
    }

    while (getline(measurementFile, line))
    {   
        vector<string> row;
        int pos = 0;
        while ((pos = line.find(';')) != string::npos) {
            row.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        row.push_back(line); // Ajouter le dernier champ

        // Créer un objet Measurement
        Measurement measurement;
        measurement.setTimestamp(row[0]);
        measurement.setSensorId(row[1]);
        measurement.setAttributeId(row[2]);
        measurement.setValue(stof(row[3]));

        // Ajouter la mesure à la map
        this->measurements[row[1]].push_back(measurement);
    }

    measurementFile.close();
    return true;
}


//Mathode qui renvoie un sensor grâce à son ID depuis la map
Sensor Model::getSensor(string sensorId){
    if (this->sensors.find(sensorId) == this->sensors.end())
    {
        return Sensor();
    } else {
        return this->sensors[sensorId];
    }
}

// Méthode qui renvoie un User via sa clé dans la map "users"
User Model::GetUser(string key)
{
    // users est une map de <string,User>
    // si la clé est trouvé dans la map, on retourne le User associé
    if (this->users.find(key) == this->users.end()) // user not founnd
    {
        return User();
    } else {
        return this->users[key];
    }
}


//Méthode qui renvoie tous les users chargés depuis les fichiers CSV : "users" & "providers"
vector<User> Model::getAllUsers()
{
    vector<User> users;
    for (map<string, User>::iterator it = this->users.begin(); it != this->users.end(); ++it)
    {
        users.push_back(it->second);
    }
    return users;
}


// Méthode qui renvoie tous les sensors chargés depuis le fichier CSV "Senssors"
map<string, Sensor> Model::getAllSensors()
{
    return this->sensors;
}



// Méthode qui renvoie les measurements associées à un capteur donné, pour un attribut donné (O2,NO2,SO2,PM10)
vector<Measurement> Model::getMeasurements(string sensorId, int count, string attribute)
{
    vector<Measurement> measurements;

    if (this->measurements.find(sensorId) == this->measurements.end())
    {
        return measurements;
    }

    vector<Measurement>& sensorMeasurements = this->measurements[sensorId];

    // Dans le fichier CSV "Measurements" les mesures sont dans l'ordre des mesures les plus
    // anciennes vers les plus récente à mesure que l'on descend dans le fichier 
    // Donc pour avoir les mesures les plus récentes je dois parcourir la structure de données à l'envers avec un "reverse iterator"

    for (vector<Measurement>::reverse_iterator it = sensorMeasurements.rbegin(); it != sensorMeasurements.rend(); ++it)
    {
        const Measurement& measurement = *it;
        if (measurement.getAttributeId() == attribute)
        {
            measurements.push_back(measurement);
            if (measurements.size() == count) //Si on a déjà récupéré count mesures, on sort de la boucle
            {
                break;
            }
        }
    }

    return measurements;
}
