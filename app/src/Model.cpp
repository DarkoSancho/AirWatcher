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
#include <cerrno>
#include <string.h>
#include <iomanip>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <cmath>
//------------------------------------------------------ Include personnel
#include "Model.h"
#include "PrivateIndividual.h"
#include "Date.h"
#include "Util.h"


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



// Méthode qui renvoie les measurements associées à un capteur donné, pour un attribut donné (O2,NO2,SO2,PM10), si on ne veut pas de count pardéfault cela vaut -1
vector<Measurement> Model::getMeasurements(string sensorId , string attribute, int count)
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


Stats Model::getData(string sensorId, Date startDate, Date EndDate, int Th03, int ThNO2, int ThSO2, int ThPM10 ){
 
    Stats Stat;
    Util util;
    vector<Measurement> resultsO3 = getMeasurements( sensorId, "03");
    vector<Measurement> resultsNO2 = getMeasurements( sensorId, "NO2");
    vector<Measurement> resultsSO2 = getMeasurements( sensorId, "SO2");    
    vector<Measurement> resultsPM10 = getMeasurements( sensorId, "PM10");

    vector<float> values03, valuesNO2, valuesSO2, valuesPM10;
    for (const Measurement& m : resultsO3) {
        if (m.getTimestamp() <= EndDate && m.getTimestamp() >= startDate) {

            values03.push_back(m.getValue());
        }
    }
    for (const Measurement& m : resultsNO2) {
        if (m.getTimestamp() <= EndDate && m.getTimestamp() >= startDate) {
            valuesNO2.push_back(m.getValue());
        }
    }
    for (const Measurement& m : resultsSO2) {
        if (m.getTimestamp() <= EndDate && m.getTimestamp() >= startDate) {            
            valuesSO2.push_back(m.getValue());
    }
    }
    for (const Measurement& m : resultsPM10) {
        if (m.getTimestamp() <= EndDate && m.getTimestamp() >= startDate) {
        valuesPM10.push_back(m.getValue());
        }
    }

    Stat.average = {
        { "O3",   values03.empty()   ? -1 : util.getAverage(values03) },
        { "NO2",  valuesNO2.empty()  ? -1 : util.getAverage(valuesNO2) },
        { "SO2",  valuesSO2.empty()  ? -1 : util.getAverage(valuesSO2) },
        { "PM10", valuesPM10.empty() ? -1 : util.getAverage(valuesPM10) }
    };

    Stat.maximum = {
        { "O3",   values03.empty()   ? -1 : util.getMax(values03) },
        { "NO2",  valuesNO2.empty()  ? -1 : util.getMax(valuesNO2) },
        { "SO2",  valuesSO2.empty()  ? -1 : util.getMax(valuesSO2) },
        { "PM10", valuesPM10.empty() ? -1 : util.getMax(valuesPM10) }
    };

    Stat.minimum = {
        { "O3",   values03.empty()   ? -1 : util.getMin(values03) },
        { "NO2",  valuesNO2.empty()  ? -1 : util.getMin(valuesNO2) },
        { "SO2",  valuesSO2.empty()  ? -1 : util.getMin(valuesSO2) },
        { "PM10", valuesPM10.empty() ? -1 : util.getMin(valuesPM10) }
    };

    Stat.sdeviation = {
        { "O3",   values03.empty()   ? -1 : util.getSdeviation(values03) },
        { "NO2",  valuesNO2.empty()  ? -1 : util.getSdeviation(valuesNO2) },
        { "SO2",  valuesSO2.empty()  ? -1 : util.getSdeviation(valuesSO2) },
        { "PM10", valuesPM10.empty() ? -1 : util.getSdeviation(valuesPM10) }
    };

    Stat.excedances = {
        { "O3",   values03.empty()   ? -1 : util.getNExceedances(values03, Th03) },
        { "NO2",  valuesNO2.empty()  ? -1 : util.getNExceedances(valuesNO2, ThNO2) },
        { "SO2",  valuesSO2.empty()  ? -1 : util.getNExceedances(valuesSO2, ThSO2) },
        { "PM10", valuesPM10.empty() ? -1 : util.getNExceedances(valuesPM10, ThPM10) }
    };
    // Work on amtmo map:
    map<Date, float> atmo;

    map<Date, list<int> > valueDayO3;
    map<Date, list<int> > valueDayNO2;
    map<Date, list<int> > valueDaySO2;
    map<Date, list<int> > valueDayPM10;
    for (const Measurement& m : resultsO3) {
        if (valueDayO3.find(m.getTimestamp()) == valueDayO3.end()) {
            valueDayO3[m.getTimestamp()] = {util.indiceO3(m.getValue())};

            if (atmo.find(m.getTimestamp())  == atmo.end()){
                atmo[m.getTimestamp()] = 0;
            }
        }
        else{
            valueDayO3[m.getTimestamp()].push_back(util.indiceO3(m.getValue()));
        }
    }
 
    for (const Measurement& m : resultsNO2) {
    if (valueDayNO2.find(m.getTimestamp()) == valueDayNO2.end()) {
        valueDayNO2[m.getTimestamp()] = {util.indiceNO2(m.getValue())};
        if (atmo.find(m.getTimestamp())  == atmo.end()){
            atmo[m.getTimestamp()] = 0;
        }
        } 
    else {
        valueDayNO2[m.getTimestamp()].push_back(util.indiceNO2(m.getValue()));
        }
    }

    for (const Measurement& m : resultsSO2) {
        if (valueDaySO2.find(m.getTimestamp()) == valueDaySO2.end()) {
            valueDaySO2[m.getTimestamp()] = {util.indiceSO2(m.getValue())};
            if (atmo.find(m.getTimestamp())  == atmo.end()){
                atmo[m.getTimestamp()] = 0;
            }
        } else {
            valueDaySO2[m.getTimestamp()].push_back(util.indiceSO2(m.getValue()));
        }
    }
    for (const Measurement& m : resultsPM10) {
        if (valueDayPM10.find(m.getTimestamp()) == valueDayPM10.end()) {
            valueDayPM10[m.getTimestamp()] = {util.indicePM10(m.getValue())};
            if (atmo.find(m.getTimestamp())  == atmo.end()){
                atmo[m.getTimestamp()] = 0;
            }
            
        } else {
            valueDayPM10[m.getTimestamp()].push_back(util.indicePM10(m.getValue()));
        }
    }

    // Calcul de l'ATMO
    map<Date, float> atmoO3;
    map<Date, float> atmoNO2;
    map<Date, float> atmoSO2;
    map<Date, float> atmoPM10;
 

    for (auto it= valueDayO3.begin(); it!= valueDayO3.end(); it++){
        atmoO3[it->first] = util.getAverage(it->second);
    }

    for (auto it = valueDayNO2.begin(); it != valueDayNO2.end(); ++it) {
        atmoNO2[it->first] = util.getAverage(it->second);
    }
    for (auto it = valueDaySO2.begin(); it != valueDaySO2.end(); ++it) {
        atmoSO2[it->first] = util.getAverage(it->second);
    }
    for (auto it = valueDayPM10.begin(); it != valueDayPM10.end(); ++it) {
        atmoPM10[it->first] = util.getAverage(it->second);
    }
    // Calcul de l'ATMO

    for (auto it = atmo.begin(); it!= atmo.end(); ++it){
        Date date = it-> first;
        list<float> value;
        if (atmoO3.find(date) != atmoO3.end()) {
            value.push_back(atmoO3[date]);
        }
        if (atmoNO2.find(date) != atmoNO2.end()) {
            value.push_back(atmoNO2[date]);
        }
        if (atmoSO2.find(date) != atmoSO2.end()) {
            value.push_back(atmoSO2[date]);
        }
        if (atmoPM10.find(date) != atmoPM10.end()) {
            value.push_back(atmoPM10[date]);
        }
        atmo[date] = util.getMax(value);
    }
    map<Date, int> atmoRound;
    for (const auto& pair : atmo) {
        atmoRound[pair.first] = static_cast<int>(std::round(pair.second));
    }
    Stat.atmo = atmoRound;

    Stat.matmo = util.getMin(atmoRound);

    Stat.Matmo = util.getMax(atmoRound); 

    return Stat;
  
}
int Model::airQualityGeo (float latitude , float longitude ,  Date start_date , Date end_date , float radius) 
    {
        
        Util util ; 
        
        vector<Sensor> sensorsSpecifiques ; 
         
        map<string,Sensor>::iterator it ; 
         
        for (it = sensors.begin() ; it != sensors.end() ; it++ )
        {
            if (latitude - radius <= it->second.getLatitude() && latitude + radius >= it->second.getLatitude() 
                && longitude - radius <= it->second.getLongitude() && longitude + radius >= it->second.getLongitude() ) 
                {
                    sensorsSpecifiques.push_back(it->second) ; 
                }
        }
        if (sensorsSpecifiques.empty()) {
        cout << "No sensors found within the radius" << endl;
        return -1;  // Ou toute autre valeur indicative d'erreur
        }   
    
        vector<float> resultsO3 ; 
        vector<float> resultsNO2 ;
        vector<float> resultsSO2 ;
        vector<float> resultsPM10 ;
        
        for ( int i = 0 ; i!= sensorsSpecifiques.size() ; i++ )
        {
            vector<Measurement> mesuresO3 = this->getMeasurements( sensorsSpecifiques[i].getSensorId(), "O3");
            vector<Measurement> mesuresSO2 = this->getMeasurements( sensorsSpecifiques[i].getSensorId(), "SO2");
            vector<Measurement> mesuresNO2 = this->getMeasurements( sensorsSpecifiques[i].getSensorId(), "NO2");
            vector<Measurement> mesuresPM10 = this->getMeasurements( sensorsSpecifiques[i].getSensorId(), "PM10");
            for (const Measurement& m : mesuresO3) {
                if (m.getTimestamp() <= end_date && m.getTimestamp() >= start_date) {

                    resultsO3.push_back(m.getValue());
                }
            }
            for (const Measurement& m : mesuresNO2) {
                if (m.getTimestamp() <= end_date && m.getTimestamp() >= start_date) {
                    resultsNO2.push_back(m.getValue());
                }
            }
            for (const Measurement& m : mesuresSO2) {
                if (m.getTimestamp() <= end_date && m.getTimestamp() >= start_date) {            
                    resultsSO2.push_back(m.getValue());
            }
            }
            for (const Measurement& m :mesuresPM10) {
                if (m.getTimestamp() <= end_date && m.getTimestamp() >= start_date) {
                    resultsPM10.push_back(m.getValue());
                }
            }
        }
         
        float avgO3 ,avgNO2 , avgSO2 ,avgPM10 ;  
        if (resultsO3.empty() ) {avgO3 = 0 ; } else  {avgO3 = util.getMax(resultsO3) ; } ; 
        if (resultsNO2.empty() ) {avgNO2 = 0 ; } else  {avgNO2 = util.getMax(resultsNO2) ; } ; 
        if (resultsSO2.empty() ) {avgSO2 = 0 ; } else  {avgSO2 = util.getMax(resultsSO2) ; } ; 
        if (resultsPM10.empty() ) {avgPM10 = 0 ; } else  {avgPM10 = util.getMax(resultsPM10) ; } ; 
        
        return util.indiceATMO( avgO3 , avgNO2 , avgSO2 ,avgPM10  ) ; 
    }


