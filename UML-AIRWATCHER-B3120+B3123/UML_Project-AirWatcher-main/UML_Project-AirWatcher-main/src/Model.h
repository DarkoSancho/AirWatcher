//---------- Interface de la classe <Model> (fichier Model.h) ----------------

#if ! defined ( MODEL_H )
#define MODEL_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include <ctime>
#include <map>
using namespace std;

#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Provider.h"
#include "Cleaner.h"
#include "Account.h"

//------------------------------------------------------------------------

class Model
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    Account GetAccount(string key);

    vector<float> calculateMeanAirQuality(float latitude, float longitude, float radius, time_t start, time_t end);

    map<float, Sensor> scoreAndRankSensors(Sensor referenceSensor, int resultCount, string attribute);

    float calculateSimilarity(vector<Measurement> reference, vector<Measurement> other);

    Sensor getSensor(string sensorId);
    
    map<string, Sensor> getAllSensors();

    vector<Measurement> getMeasurements(string sensorId, int count, string attribute);

    vector<Account> getAllAccounts();

//-------------------------------------------- Constructeurs - destructeur
    Model ( );

    virtual ~Model ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    bool loadSensorsData(string pathSensorCSV, string pathMeasureCSV, string pathAttributeCSV);
 
    bool loadCleaners(string pathCleanerCSV);

    bool loadUsersData(string pathUserCSV, string pathProviderCSV);


//----------------------------------------------------- Attributs protégés
map<string,Sensor> sensors; 
map<string,Attribute> attributes;
map<string,vector<Measurement>> measurments;
map<string,Provider> providers;
map<string,Cleaner> cleaners;
map<string,Account> accounts;

};

//-------------------------------- Autres définitions dépendantes de <Model>

#endif // MODEL_H