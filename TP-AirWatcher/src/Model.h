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