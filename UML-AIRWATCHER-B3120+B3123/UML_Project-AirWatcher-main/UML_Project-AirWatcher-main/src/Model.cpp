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
#include "Utility.h"

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
    string pathUserCSV = "resources/users.csv";
    string pathProviderCSV = "resources/providers.csv";
    string pathCleanerCSV = "resources/cleaners.csv";
    string pathSensorCSV = "resources/sensors.csv";
    string pathMeasureCSV = "resources/measurements.csv";
    string pathAttributeCSV = "resources/attributes.csv";

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
    // lecture des utilisateurs 
    ifstream userFile(pathUserCSV);
    if (!userFile.is_open())
    {
        cerr << "Error: cannot open file " << pathUserCSV << strerror(errno) << endl;
        return false;
    }

    string line;
    while ( getline ( userFile, line ) ) 
    {
        vector<string> row;
        string field;
        stringstream liness(line);
        // Lire chaque champ de la ligne
        while (getline(liness, field, ';'))
        {
            row.push_back(field);
        }
        // Créer un objet User
        PrivateIndividual individualUser;
        individualUser.setAccountID(row[0]);
        individualUser.setPrivilege(PRIVATE_INDIVIDUAL);
        string sensorId = row[1];
        
        // Ajouter le user à la map de la forme <idUser, user>
        this->accounts[row[0]] = individualUser;
    }

    // lecture des Providers
    ifstream providerFile(pathProviderCSV);
    if (!providerFile.is_open())
    {
        cerr << "Error: cannot open file " << pathProviderCSV << strerror(errno) << endl;
        return false;
    }

    while ( getline ( providerFile, line ) ) 
    {
        vector<string> row;
        string field;
        stringstream liness(line);
        // Lire chaque champ de la ligne
        while (getline(liness, field, ';'))
        {
            row.push_back(field);
        }
        // Créer un objet User
        Provider provider;
        provider.setAccountID(row[0]);
        provider.setPrivilege(PROVIDER);

        // Ajouter le user à la map de la forme <idUser, user>
        this->providers[row[0]] = provider;
        this->accounts[row[0]] = provider;
    }
    
    return true ; 
}

bool Model::loadCleaners(string pathCleanerCSV)
{
    ifstream file(pathCleanerCSV);
    if (!file.is_open()) {
        cerr << "Error: cannot open file " << pathCleanerCSV << ": " << strerror(errno) << std::endl;
        return false;
    }
    // Lire le fichier csv ligne par ligne
    string line;
    vector<string> row;
    string field;
    while (getline(file, line))
    {   
        stringstream liness(line);
        // Lire chaque champ de la ligne
        while (getline(liness, field, ';'))
        {
            row.push_back(field);
        }
        // Créer un objet AirCleaner
        Cleaner cleaner;
        cleaner.setCleanerId(row[0]); // Convert string to float
        cleaner.setLatitude(stof(row[1]));
        cleaner.setLongitude(stof(row[2]));
        cleaner.setStartTime(Utility::convertToTimeT(row[3]));
        cleaner.setEndTime(Utility::convertToTimeT(row[4]));

        // Ajouter le cleaner à la map de la forme <idCleaner, cleaner>
        this->cleaners[row[0]] = cleaner;
        // Vider la ligne
        row.clear();
    }
    file.close();
    return true ; 
}

bool Model::loadSensorsData(string pathSensorCSV, string pathMeasureCSV, string pathAttributeCSV)
{
    // chargement de tous les sensors
    ifstream sensorFile(pathSensorCSV);
    if (!sensorFile.is_open()) {
        cerr << "Error: cannot open file " << pathSensorCSV << ": " << strerror(errno) << std::endl;
        return false;
    }

    // Lire le fichier csv ligne par ligne
    string line;
    while (getline(sensorFile, line))
    {   
        vector <string> row;
        string field;
        stringstream liness(line);
        // Lire chaque champ de la ligne
        while (getline(liness, field, ';'))
        {
            row.push_back(field);
        }
        // Créer un objet Sensor
        Sensor sensor;
        sensor.setSensorId(row[0]);
        sensor.setLatitude(stof(row[1]));
        sensor.setLongitude(stof(row[2]));
        sensor.setFlagged(false);
        // Ajouter le sensor à la map de la forme <idSensor, sensor>
        this->sensors[row[0]] = sensor;
    }
    sensorFile.close();

    // chargement de toutes les mesures
    ifstream measurementFile(pathMeasureCSV);
    if (!measurementFile.is_open()) {
        cerr << "Error: cannot open file " << pathMeasureCSV << ": " << strerror(errno) << std::endl;
        return false;
    }

    while (getline(measurementFile, line))
    {   
        vector <string> row;
        string field;

        // Lire la première ligne
        stringstream liness(line);
        // Lire chaque champ de la ligne
        while (getline(liness, field, ';'))
        {
            row.push_back(field);
        }

        // Créer un objet Measurement
        Measurement measurement;
        measurement.setTimestamp(Utility::convertToTimeT(row[0]));
        measurement.setSensorId(row[1]);
        measurement.setAttributeId(row[2]);
        measurement.setValue(stof(row[3]));

        // Ajouter la mesure à la map de la forme <idSensor, vector<Measurement> >
        this->measurments[row[1]].push_back(measurement);
    }

    return true ; 
}

vector<float> Model::calculateMeanAirQuality(float latitude, float longitude, float radius, time_t start, time_t end){
    float meanNO2 = 0.0;
    float meanO3 = 0.0;
    float meanPM10 = 0.0;
    float meanSO2 = 0.0;
    int no2Count = 0;
    int o3Count = 0;
    int pm10Count = 0;
    int so2Count = 0;
    int sensorCount=0;

    for (auto &sensor : this->sensors)
    {
        if (Utility::isWithinRadius(sensor.second.getLatitude(), sensor.second.getLongitude(), latitude, longitude, radius))
        {
            sensorCount++;
            for (auto &measurement : this->measurments[sensor.first])
            {
                if (measurement.getTimestamp() >= start && measurement.getTimestamp() <= end)
                {
                    if (measurement.getAttributeId() == "NO2")
                    {
                        meanNO2 += measurement.getValue();
                        no2Count++;
                    }
                    else if (measurement.getAttributeId() == "O3")
                    {
                        meanO3 += measurement.getValue();
                        o3Count++;
                    }
                    else if (measurement.getAttributeId() == "PM10")
                    {
                        meanPM10 += measurement.getValue();
                        pm10Count++;
                    }
                    else if (measurement.getAttributeId() == "SO2")
                    {
                        meanSO2 += measurement.getValue();
                        so2Count++;
                    } else {
                        cerr << "Error: unknown attribute " << measurement.getAttributeId() << endl;
                    
                    }
                }
            }
        }
    }

    if (no2Count > 0)
    {
        meanNO2 /= no2Count;
    }
    if (o3Count > 0)
    {
        meanO3 /= o3Count;
    }
    if (pm10Count > 0)
    {
        meanPM10 /= pm10Count;
    }
    if (so2Count > 0)
    {
        meanSO2 /= so2Count;
    }

    if (sensorCount == 0)
    {
        return {};
    }

    return {meanNO2, meanO3, meanPM10, meanSO2};
}

Sensor Model::getSensor(string sensorId){
    if (this->sensors.find(sensorId) == this->sensors.end())
    {
        return Sensor();
    } else {
        return this->sensors[sensorId];
    }
}

Account Model::GetAccount(string key)
{
    // accounts is map of <string, Account>
    // if key is found inside the strings, return the Account
    if (this->accounts.find(key) == this->accounts.end())
    {
        return Account();
    } else {
        return this->accounts[key];
    }
}

vector<Account> Model::getAllAccounts()
{
    vector<Account> accounts;
    for (auto &account : this->accounts)
    {
        accounts.push_back(account.second);
    }
    return accounts;
}

map<float, Sensor> Model::scoreAndRankSensors(Sensor referenceSensor, int resultCount, string attribute) {
    // A partir d'un Sensor de référence, on calcule un score de similarité avec les autres Sensors
    // On récupère les 10 derniers relevés de chaque Sensor
    // On calcule la similarité entre les Sensors avec un indice de Jaccard
    // On classe les Sensors par ordre décroissant de similarité
    // On retourne les resultCount Sensors les plus similaires

    
    map<float, Sensor> rankMap;
    for (auto &sensor : this->sensors)
    {
        if (sensor.first != referenceSensor.getSensorId())
        {
            float similarity = calculateSimilarity(getMeasurements(referenceSensor.getSensorId(), 10, attribute), getMeasurements(sensor.first, 10, attribute));
            rankMap[similarity] = sensor.second;
        }
    }

    // Return only the top resultCount sensors
    map<float, Sensor> topRankMap;
    int count = 0;
    for (auto &rank : rankMap)
    {
        if (count == resultCount)
        {
            break;
        }
        topRankMap[rank.first] = rank.second;
        count++;
    }

    return topRankMap;
}

float Model::calculateSimilarity(vector<Measurement> reference, vector<Measurement> other) {
    // Calcul de l'indice de Jaccard entre deux vecteurs de mesures
    // On considère que les mesures sont triées par ordre croissant de timestamp
    // On ne considère que les timestamps communs aux deux vecteurs
    // On calcule la somme des valeurs absolues des différences entre les mesures
    // On divise par la somme des valeurs absolues des mesures du vecteur de référence
    // On retourne 1 - ce ratio

    // On suppose que les deux vecteurs de mesures ont été triés par ordre croissant de timestamp
    int i = 0;
    int j = 0;
    float sum = 0;
    while (i < reference.size() && j < other.size())
    {
        if (reference[i].getTimestamp() == other[j].getTimestamp())
        {
            sum += abs(reference[i].getValue() - other[j].getValue());
            i++;
            j++;
        }
        else if (reference[i].getTimestamp() < other[j].getTimestamp())
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    float similarity = 1 - sum / i;
    return abs(similarity);
}

map<string, Sensor> Model::getAllSensors()
{
    return this->sensors;
}

vector<Measurement> Model::getMeasurements(string sensorId, int count, string attribute)
{
    vector<Measurement> measurements;
    if (this->measurments.find(sensorId) == this->measurments.end())
    {
        return measurements;
    }
    for (auto it = this->measurments[sensorId].rbegin(); it != this->measurments[sensorId].rend(); ++it)
    {
        const Measurement& measurement = *it;
        if (measurement.getAttributeId() == attribute)
        {
            measurements.push_back(measurement);
            if (measurements.size() == count)
            {
                break;
            }
        }
    }
    return measurements;
}