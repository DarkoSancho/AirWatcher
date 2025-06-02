


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
#include "util.h"
#include <set>



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


bool Model::isSensorReliable(string sensorId)
{
    bool reliability = true;
    Sensor sensor_reference = getSensor(sensorId);
    float lat = sensor_reference.getLatitude();
    float lng = sensor_reference.getLongitude();

    // Valeur fixe pour l'écart-type maximum acceptable
    float max_std_deviation = 50.0;
    
    // Valeurs max acceptables
    float max_acceptable_O3 = 100.0;  
    float max_acceptable_NO2 = 100.0;  
    float max_acceptable_SO2 = 100.0; 
    float max_acceptable_PM10 = 100.0; 
    

    // Récupération des mesures pour chaque attribut
    vector<Measurement> resultsO3 = getAllMeasurementsForAttribute("O3");
    vector<Measurement> resultsNO2 = getAllMeasurementsForAttribute("NO2");
    vector<Measurement> resultsSO2 = getAllMeasurementsForAttribute("SO2");
    vector<Measurement> resultsPM10 = getAllMeasurementsForAttribute("PM10");

    // Extraire les valeurs pour calculer l'écart-type
    vector<float> valuesO3, valuesNO2, valuesSO2, valuesPM10;
    for (const Measurement& m : resultsO3) {
        string sensorId_compare = m.getSensorId();
        Sensor sensor_compare = getSensor(sensorId_compare);
        float lat_compare = sensor_compare.getLatitude();
        float long_compare = sensor_compare.getLongitude();
        if (calculateDistance(lat, lng, lat_compare, long_compare) <= 5)
        {
            valuesO3.push_back(m.getValue());
        }
        
    }
    for (const Measurement& m : resultsNO2) {
        string sensorId_compare = m.getSensorId();
        Sensor sensor_compare = getSensor(sensorId_compare);
        float lat_compare = sensor_compare.getLatitude();
        float long_compare = sensor_compare.getLongitude();
        if (calculateDistance(lat, lng, lat_compare, long_compare) <= 5)
        {
            valuesNO2.push_back(m.getValue());
        }
    }
    for (const Measurement& m : resultsSO2) {
        string sensorId_compare = m.getSensorId();
        Sensor sensor_compare = getSensor(sensorId_compare);
        float lat_compare = sensor_compare.getLatitude();
        float long_compare = sensor_compare.getLongitude();
        if (calculateDistance(lat, lng, lat_compare, long_compare) <= 5)
        {
            valuesSO2.push_back(m.getValue());
        }
    }
    for (const Measurement& m : resultsPM10) {
        string sensorId_compare = m.getSensorId();
        Sensor sensor_compare = getSensor(sensorId_compare);
        float lat_compare = sensor_compare.getLatitude();
        float long_compare = sensor_compare.getLongitude();
        if (calculateDistance(lat, lng, lat_compare, long_compare) <= 5)
        {
            valuesPM10.push_back(m.getValue());
        }
    }

    // Utiliser l'objet Util pour calculer les écarts-types
    Util util;
    
    // Ne calculer l'écart-type que s'il y a des mesures disponibles
    float stdDevO3 = valuesO3.empty() ? 0 : util.getSdeviation(valuesO3);
    float stdDevNO2 = valuesNO2.empty() ? 0 : util.getSdeviation(valuesNO2);
    float stdDevSO2 = valuesSO2.empty() ? 0 : util.getSdeviation(valuesSO2);
    float stdDevPM10 = valuesPM10.empty() ? 0 : util.getSdeviation(valuesPM10);

    // Vérifier si les écarts-types sont en dessous du seuil maximum 
    if ((!valuesO3.empty() && stdDevO3 > max_std_deviation) || 
        (!valuesNO2.empty() && stdDevNO2 > max_std_deviation) || 
        (!valuesSO2.empty() && stdDevSO2 > max_std_deviation) || 
        (!valuesPM10.empty() && stdDevPM10 > max_std_deviation)) {
        reliability = false;
    }

    // Vérifier si les valeurs sont dans des plages réalistes
    if (!valuesO3.empty()) {
        float maxO3 = util.getMax(valuesO3);
        if (maxO3 > max_acceptable_O3) {
            reliability = false;
        }
    }
    
    if (!valuesNO2.empty()) 
    {
        float maxNO2 = util.getMax(valuesNO2);
        if (maxNO2 > max_acceptable_NO2) {
            reliability = false;
        }
    }
    
    if (!valuesSO2.empty()) 
    {
        float maxSO2 = util.getMax(valuesSO2);
        if (maxSO2 > max_acceptable_SO2) {
            reliability = false;
        }
    }
    
    if (!valuesPM10.empty()) 
    {
        float maxPM10 = util.getMax(valuesPM10);
        if (maxPM10 > max_acceptable_PM10) {
            reliability = false;
        }
    }

    return reliability;
}


float Model::calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    const float R = 6371.0; // Rayon de la Terre en kilomètres
    
    // Conversion des latitudes et longitudes en radians
    float latRad1 = lat1 * M_PI / 180.0;
    float lonRad1 = lon1 * M_PI / 180.0;
    float latRad2 = lat2 * M_PI / 180.0;
    float lonRad2 = lon2 * M_PI / 180.0;
    
    // Différences de coordonnées
    float dLat = latRad2 - latRad1;
    float dLon = lonRad2 - lonRad1;
    
    // Formule de Haversine
    float a = sin(dLat/2) * sin(dLat/2) + cos(latRad1) * cos(latRad2) * sin(dLon/2) * sin(dLon/2);
    float c = 2 * atan2(sqrt(a), sqrt(1-a));
    float distance = R * c;
    
    return distance;
}


vector<Measurement> Model::getAllMeasurementsForAttribute(string attribute)
{
    vector<Measurement> result;


    Date startDate = Date ( 1, 1, 2019, 12, 0, 0 );
    Date endDate =  Date ( 31, 12, 2019, 12, 0, 0 );

    for (const auto& pair : sensors) {
        const string& sensorId = pair.first;
        vector<Measurement> partial = getMeasurements(sensorId,100, attribute);
        result.insert(result.end(), partial.begin(), partial.end());
    }
    return result;
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


//------- ***** ça commence ici Yassine pour te repérer *****----------------

// Méthode qui renvoie les measurements associées à un capteur donné, pour un attribut donné (O2,NO2,SO2,PM10), si on ne veut pas de count pardéfault cela vaut -1
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


//surcharge 
vector<Measurement> Model::getMeasurements(string sensorId, string attribute) {
    vector<Measurement> measurements;

    // Vérifie si le capteur existe dans la map
    if (this->measurements.find(sensorId) == this->measurements.end()) {
        return measurements; // Capteur non trouvé → retourne vecteur vide
    }

    vector<Measurement>& sensorMeasurements = this->measurements[sensorId];

    // Parcours normal (ordre chronologique) — car pas besoin ici des N dernières mesures
    for (const Measurement& measurement : sensorMeasurements) {
        if (measurement.getAttributeId() == attribute) {
            measurements.push_back(measurement);
        }
    }

    return measurements;
}



// This method calculates a similarity score between two sensors based on an average of their measurements.
// It calculates and compares these averages for each of four attributes: O3, NO2, SO2, and PM10,
// and only considers values within the given date range.
// The final score is normalized between 0 and 100 (the closer to 100, the more similar).
// Parameters:
//   referenceSensor  The reference sensor to compare against.
//   compareSensor    The sensor being compared to the reference sensor.
//   startDate        The start date of the time interval for measurements to consider.
//   endDate          The end date of the time interval for measurements to consider.
// return : A similarity score (double) between 0.0 and 100.0. A value close to 100 indicates high similarity.
double Model::calculateSimilarity(const Sensor& referenceSensor, const Sensor& compareSensor, const Date& startDate, const Date& endDate)
{
    const string attributes[] = {"O3", "NO2", "SO2", "PM10"};
    double totalDifference = 0.0;
    int attributeCount = 0;

    for (const string& attribute : attributes)
    {
        vector<Measurement> referenceMeasurements = this->getMeasurements(referenceSensor.getSensorId(), -1, attribute);
        vector<Measurement> compareMeasurements = this->getMeasurements(compareSensor.getSensorId(), -1, attribute);
        double refSum = 0.0, cmpSum = 0.0;
        int refCount = 0, cmpCount = 0;

        if (referenceMeasurements.empty() || compareMeasurements.empty()) {
            continue;
        }

        for (const auto& m : referenceMeasurements) {
            Date d(m.getTimestamp());
            if (d >= startDate && d <= endDate) {
                refSum += m.getValue();
                refCount++;
            }
        }

        for (const auto& m : compareMeasurements) {
            Date d(m.getTimestamp());
            if (d >= startDate && d <= endDate) {
                cmpSum += m.getValue();
                cmpCount++;
            }
        }

        // si au moins une mesure valide pour chaque capteur
        if (refCount > 0 && cmpCount > 0) {
            double refAvg = refSum / refCount;
            double cmpAvg = cmpSum / cmpCount;
            double diff = abs(refAvg - cmpAvg);
            totalDifference += diff;
            attributeCount++;
        }
    }

    // si pas de donnÃ©es exploitables
    if (attributeCount == 0) {
        return 0.0;  
    }

    double averageDifference = totalDifference / attributeCount; // attributCount vaut toujours 4

    return 100.0 / (1.0 + averageDifference);  
}



// This method compares a given sensor to all other loaded sensors and computes a similarity score
// based on measurements from a defined date range. It returns a sorted list of sensor IDs
// with their similarity scores, showing only the top 5 most similar sensors.
// Parameters:
//   referenceSensorID  The ID of the reference sensor.
//   startDate          The start date of the time interval for measurements to consider.
//   endDate            The end date of the time interval for measurements to consider.
// return : A vector of pairs (sensor ID, similarity score), sorted by similarity (highest first).
//          Contains up to 5 sensors most similar to the reference.
vector<pair<string, double>> Model :: compareSensors( const string& referenceSensorID, const Date& startDate,  const Date& endDate)
{
    vector<pair<string, double>> similarityScores; // A vector allows us to sort sensors by similarity score

    Sensor referenceSensor = getSensor(referenceSensorID);
    if (referenceSensor.getSensorId().empty()) {
        cerr << "Reference sensor not found!" << endl;
        return similarityScores;
    }

    for (map<string, Sensor>::const_iterator it = sensors.begin(); it != sensors.end(); ++it)
    {
        const string& sensorID = it->first;
        const Sensor& sensor = it->second;

        if (sensorID == referenceSensorID) // Avoid comparing the sensor with itself
            continue;

        double score = calculateSimilarity(referenceSensor, sensor, startDate, endDate);
        similarityScores.push_back(pair<string, double>(sensorID, score));
    }

    sort(similarityScores.begin(), similarityScores.end(),
         [](const pair<string, double>& a, const pair<string, double>& b) {
             return a.second > b.second;
         });

    // Keep only the top 5 elements, or fewer if there are less than 5
    if (similarityScores.size() > 5) {
        similarityScores.resize(5); // Resize the vector to keep only the top 5
    }

    return similarityScores;
}



/* This Method computes the average air quality in a given geographic area over a specified time period.
 * 
 * This method iterates over all sensors stored in the model. For each sensor located within a given radius 
 * of a specified point (latitude, longitude), it retrieves all measurements that fall within the given time interval [start, end].
 * 
 * It then computes the average values for the following air quality attributes:
 * - NO2 (Nitrogen Dioxide)
 * - O3  (Ozone)
 * - PM10 (Particulate Matter 10µm)
 * - SO2 (Sulfur Dioxide)
 * 
 * @param latitude Latitude of the center point of the area to analyze.
 * @param longitude Longitude of the center point of the area to analyze.
 * @param start Start date of the time interval.
 * @param end End date of the time interval.
 * @param radius Radius (in the same unit as latitude/longitude) around the center point to include sensors.
 * 
 * @return A vector containing the average values in the following order: [NO2, O3, PM10, SO2]. 
 *         If no sensors are found within the specified radius, returns an empty vector and prints an error message.
 */


vector<float> Model::airQualityGeo(float latitude, float longitude, Date start, Date end,  float radius){
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
        if (isWithinRadius(sensor.second.getLatitude(), sensor.second.getLongitude(), latitude, longitude, radius)) //check if the sensor is in the area that we want 
        cout << "Sensor " << sensor.first << " is within radius." << endl;
        {
            sensorCount++;
            for (auto &measurement : this->measurements[sensor.first])
            {
                if (measurement.getTimestamp() >= start && measurement.getTimestamp() <= end) // check if the measurment is in the time interval that we want 
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

    if (sensorCount == 0) //if thare is no sensors in the area
    {
        cerr << "No sensor found in radius " << radius << " at (" << latitude << ", " << longitude << ")" << endl;
        return {};
    }

    return {meanNO2, meanO3, meanPM10, meanSO2};
}

bool Model :: isWithinRadius(float lat1, float lon1, float lat2, float lon2, float radiusKm) {
    const float earthRadiusKm = 6371.0;

    float dLat = (lat2 - lat1) * M_PI / 180.0;
    float dLon = (lon2 - lon1) * M_PI / 180.0;

    float a = sin(dLat / 2) * sin(dLat / 2) +
              cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
              sin(dLon / 2) * sin(dLon / 2);

    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float distance = earthRadiusKm * c;

    return distance <= radiusKm;
}




Stats Model::getData(string sensorId, Date startDate, Date EndDate, int Th03 , int ThNO2 , int ThSO2, int ThPM10 ){
 
    Stats Stat;
    Util util;
    vector<Measurement> resultsO3 = getMeasurements( sensorId, "O3");
    vector<Measurement> resultsNO2 = getMeasurements( sensorId, "NO2");
    vector<Measurement> resultsSO2 = getMeasurements( sensorId, "SO2");    
    vector<Measurement> resultsPM10 = getMeasurements( sensorId, "PM10");

    // We store in valuesXX the valid values of component XX (dates between startDate and EndDate)
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
    // If there are not valid value: default value is -1.
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

   // To compute the daily mean, max, and min ATMO values, we calculate ATMO for each day with available data. These daily values are stored in valueDayXX maps, where the keys are Dates.
    map<Date, list<int>> valueDayO3;
    map<Date, list<int>> valueDayNO2;
    map<Date, list<int>> valueDaySO2;
    map<Date, list<int>> valueDayPM10;
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

    // As AMTO is an integer we round it with the std methode round.
    map<Date, int> atmoRound;
    for (const auto& pair : atmo) {
        atmoRound[pair.first] = static_cast<int>(std::round(pair.second));
    }
    Stat.atmo = atmoRound;

    Stat.matmo = util.getMin(atmoRound);

    Stat.Matmo = util.getMax(atmoRound); 

    return Stat;
  
}

