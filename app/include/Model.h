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
#include <algorithm>
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

    vector<Measurement> getMeasurements(string sensorId, string attribute, int count = INT_MAX );

    vector<User> getAllUsers();

    int airQualityGeo (float latitude , float longitude ,  Date start_date , Date end_date ,float radius =0 ) ;  

    Stats getData(string sensorId, Date startDate, Date EndDate, int Th03 = -1, int ThNO2 = -1, int ThSO2 = -1, int ThPM10 = -1);

    //Retun statistiques: 
    //result.average[x]: Average concentration of x component
    //result.minimum[x]: mininimum concentration of x component
    //result.maximum[x]: maximum concentration of x component
    //result.sDeviation[x]: Standard deviation of component x
    //result.excedances[x]: Numeros of excedance of component x
    //result.matmo: Pair of Day and value of highest ATMO value
    //result.matmp: Pair of Day and value of lowest ATMO value

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
map<string,vector<Measurement> > measurements;
map<string,Provider> providers;
map<string,Cleaner> cleaners;
map<string,User> users;

};

//-------------------------------- Autres définitions dépendantes de <Model>

#endif // MODEL_H;