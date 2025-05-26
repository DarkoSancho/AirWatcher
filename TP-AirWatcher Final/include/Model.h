/*

//---------- Interface de la classe <Model> (fichier Model.h) ----------------

#if ! defined ( MODEL_H )
#define MODEL_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include <ctime>
#include <map>
#include <vector> 
using namespace std;

#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Provider.h"
#include "Cleaner.h"
#include "User.h"

//------------------------------------------------------------------------

class Model
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    User GetUser(string key);

    Sensor getSensor(string sensorId);
    
    map<string, Sensor> getAllSensors();

    vector<Measurement> getMeasurements(string sensorId, int count, string attribute);

    vector<User> getAllUsers();



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
map<string,vector<Measurement>> measurements;
map<string,Provider> providers;
map<string,Cleaner> cleaners;
map<string,User> users;

};

//-------------------------------- Autres définitions dépendantes de <Model>

#endif // MODEL_H;

*/


//---------- Interface de la classe <Model> (fichier Model.h) ----------------

#if ! defined ( MODEL_H )
#define MODEL_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <list>
#include <ctime>
#include <map>
#include <vector> 
#include <climits>
using namespace std;

#include "Sensor.h"
#include "Attribute.h"
#include "Measurement.h"
#include "Provider.h"
#include "Cleaner.h"
#include "User.h"
#include "Date.h"
//------------------------------------------------------------------------

// In order to return statistics from a sensor
struct Stats {
    map<string,float> average;
    map<string,float> minimum;
    map<string,float> maximum;
    map<string,float> sdeviation;
    map<string,float> excedances;
    map<Date,int> atmo;
    pair<Date, int> matmo;
    pair<Date, int> Matmo;
};

class Model
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    User GetUser(string key);

    Sensor getSensor(string sensorId);
    
    map<string, Sensor> getAllSensors();

    //vector<Measurement> getMeasurements(string sensorId, string attribute, int count = INT_MAX );


    //vector<Measurement> getMeasurements(const string& sensorId, const string& attributeId,const Date& startDate, const Date& endDate) ; 
    vector<Measurement> getMeasurements(string sensorId, int count, string attribute); 
    vector<Measurement> getMeasurements(string sensorId, string attribute) ; 

    //vector<Measurement> getMeasurements(const string& sensorId, const string& attribute);


    vector<User> getAllUsers();


    //float airQualityGeo (float latitude , float longitude , float radius =0 , time_t start_date , time_t end_date) ;  

    Stats getData(string sensorId, Date startDate, Date EndDate, int Th03 = 180, int ThNO2 = 200, int ThSO2 = 350, int ThPM10 = 50);

    vector<pair<string, double>> compareSensors( const string& referenceSensorID, const Date& startDate,  const Date& endDate);

    //vector<pair<string, double>> compareSensors(const string& referenceSensorID, int resultCount, const string& attribute) ; 

    //float calculateSimilarity(vector<Measurement> reference, vector<Measurement> other) ; 
    double calculateSimilarity(const Sensor& referenceSensor, const Sensor& compareSensor, const Date& startDate, const Date& endDate);
    //Retun statistiques: 
    //result.average[x]: Average concentration of x component
    //result.minimum[x]: mininimum concentration of x component
    //result.maximum[x]: maximum concentration of x component
    //result.sDeviation[x]: Standard deviation of component x
    //result.excedances[x]: Numeros of excedance of component x
    //result.matmo: Pair of Day and value of highest ATMO value
    //result.matmp: Pair of Day and value of lowest ATMO value


    //surcharge de clauclate similarity 
    double calculateSimilarity(const vector<Measurement>& ref, const vector<Measurement>& cmp) ; 


//-------------------------------------------- Constructeurs - destructeur
    Model ( );

    virtual ~Model ( );

//------------------------------------------------------------------ PRIVE


//----------------------------------------------------- Méthodes protégées
    bool loadSensorsData(string pathSensorCSV, string pathMeasureCSV, string pathAttributeCSV);
 
    bool loadCleaners(string pathCleanerCSV);

    bool loadUsersData(string pathUserCSV, string pathProviderCSV);

    bool isSensorReliable(string sensorId);

    bool isWithinRadius(float lat1, float lon1, float lat2, float lon2, float radiusKm) ; 


    vector<float> airQualityGeo (float latitude , float longitude ,  Date start_date , Date end_date ,float radius =0 ) ;  

    float calculateDistance(float lat1, float lon1, float lat2, float lon2);

    vector<Measurement> getAllMeasurementsForAttribute(string attribute);

//----------------------------------------------------- Attributs protégés
protected:
map<string,Sensor> sensors; 
map<string,Attribute> attributes;
map<string,vector<Measurement>> measurements;
map<string,Provider> providers;
map<string,Cleaner> cleaners;
map<string,User> users;

};

//-------------------------------- Autres définitions dépendantes de <Model>

#endif // MODEL_H;